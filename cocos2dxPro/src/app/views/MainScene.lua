
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()

    self.uiPage = require("MainScene").create(function (path, node, funcName)
        return function(...) 
            if self[funcName] and type(self[funcName]) == "function" then
                self[funcName](self, ...)
            else
                print(string.format("[%s -> %s]: %s方法未实现", path, node:getName(), funcName))
            end
         end
    end)
    self:addChild(self.uiPage.root)

    self.uiPage.root:setContentSize(cc.Director:getInstance():getVisibleSize())
    ccui.Helper:doLayout(self.uiPage.root)

    self.uiPage.LoadingBar_Percent:setPercent(0)
    self.uiPage.Text_Percent:setString("")
    self.uiPage.Text_Status:setString("")

    print("------------------------------------")
    print("------------------------------------")
    print("------------------------------------")
    print("------------------------------------")


    local writablePath = cc.FileUtils:getInstance():getWritablePath()
    local storagePath = writablePath .. "new_version"

    -- 创建assetsManager对象
    local assetsManager = assets.AssetsManager:new_local("res/version/project_dev.manifest", storagePath, "android")
    -- 自定义资源检查函数
    assetsManager:setVerifyLuaCallback(function(fullPath, asset)
        print("fullPath", fullPath)
        print("md5", asset.md5)
        print("path", asset.path)
        print("compressed", asset.compressed)
        print("downloadSize", asset.downloadSize)
        print("fileSize", asset.fileSize)
        return true
    end)
    self.assetsManager = assetsManager

    print("storagePath", assetsManager:getStoragePath())

    self.uiPage.Button_Start:setVisible(false)

    self:onUpdate(function()
        self:setPercent(assetsManager:getUpdatePercent() * 100)
    end)
end

local function fmt(size)
    if size < 1024 then
        return string.format("%dbytes", size)
    elseif size < 1024 * 1024 then
        return string.format("%fkb", size / 1024)
    elseif size < 1024 * 1024 * 1024 then
        return string.format("%fmb", size / 1024 / 1024)
    end
    return string.format("%fgb", size / 1024 / 1024 / 1024)
end

function MainScene:onClickUpdate(sender)
    -- 检查版本
    self.assetsManager:checkUpdate(function(success, code)
        local str = "检查更新失败:"
        if success then
            str = "检查更新成功:"
        end

        if code == assets.ERROR_NO_LOCAL_MANIFEST then
            str = str .. "错误:找不到本地的清单文件"
        elseif code == assets.ERROR_DOWNLOAD_MANIFEST then
            str = str .. "错误:远程清单文件下载失败"
        elseif code == assets.ERROR_PARSE_MANIFEST then
            str = str .. "错误:清单文件解析失败"
        elseif code == assets.NEED_STRONG_UPDATE then
            str = str .. "需要强更新"
        elseif code == assets.NEW_VERSION_FOUND then
            self.uiPage.Button_Start:setVisible(true)
            str = str .. "发现新版本"

            print("需要更新大小:", fmt(self.assetsManager:getTotalSize()))

        elseif code == assets.ALREADY_UP_TO_DATE then
            str = str .. "已经是最新版本了"
        end
        print(str)
    end)
end

-- @brief 修复更新
function MainScene:onClickFixUpdate()
    print("do fixed")
    self.assetsManager:repair()
end

function MainScene:onClickStartUpdate()
    -- 升级版本
    self.assetsManager:startUpdate(function(finish, code, msg)
        local str = "更新中:"
        if finish then
            str = "更新完成:"
        end

        if code == assets.ERROR_DECOMPRESS then
            str = str .. "错误:资源解压失败"
        elseif code == assets.ERROR_DOWNLOAD then
            str = str .. "错误:有资源下载失败"
        elseif code == assets.ERROR_VERIF then
            str = str .. "错误:资源校验失败"
        elseif code == assets.SUCCESS then
            str = str .. "更新成功"
        end
        print(str, msg)
    end)
end

function MainScene:onExit()
    print("exit")
end

function MainScene:setPercent(percent)
    self.uiPage.LoadingBar_Percent:setPercent(percent)
    self.uiPage.Text_Percent:setString(string.format("%d%%", percent))
end

function MainScene:onClickNextScene(sender)
    self:getApp():run("SecondScene")
end

return MainScene
