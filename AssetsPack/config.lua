-- 平台定义
PLATFORM_ANDROID = "android"
PLATFORM_IOS 	 = "ios"
PLATFORM_WINDOWS = "windows"
PLATFORM_MAC 	 = "mac"
PLATFORM_LINUX 	 = "linux"

local httpRoot = "http://1.14.65.70:8100/game/"

local M = {}

-- 散文件模式
-- 更新单个差异文件,客户端依次下载所有的单文件
-- 如果此选项为false则会打包以前所有版本到现在版本的差异zip文件，客户端直接更新zip文件在解压即可
M["looseFileMode"] = false

-- 加密用到的sign
M["encryptsign"] = "XXTEA"

-- 加密用到的key
M["encryptkey"] = "2dxLua"

-- 主版本号（主版本号不同则表示需要强更新）
M["majorVersion"] = 0
-- 次版本号
M["minorVersion"] = 0
-- 修订号
M["revisionNumber"] = 2

-- 资源版本（重要，关系到是否更不更新）
M["version"] = string.format("%d.%d.%d", M.majorVersion, M.minorVersion, M.revisionNumber)


--local dirName = string.gsub(M["version"], "%.", "_")

-- 要下载具体内容的地址
if M.looseFileMode then
    M["packageUrl"] = string.format("%s/assets/", httpRoot)
else
    -- 整包差异更新,每个zip名称都不一样 直接放在根路径就行
    M["packageUrl"] = string.format("%s", httpRoot)
end


-- 远程的配置清单文件地址
M["remoteManifestUrl"] = string.format("%sproject_dev.manifest", httpRoot)


-- 更新描述
M["updateDescription"] = [[1:修复bug
2:增加功能
]]

-- 强更新版本(如果客户端版本小于当前版本，则客户端进行弹框提示，用户确认跳转至新版本下载地址)
M["strongUpdateVer"] = {}
-- 平台PLATFORM_ANDROID强更新版本
M["strongUpdateVer"][PLATFORM_ANDROID] 	= M["majorVersion"]
-- 平台PLATFORM_IOS强更新版本
M["strongUpdateVer"][PLATFORM_IOS] 		= M["majorVersion"]
--...

-- 强更新下载地址
M["strongUpdateURL"] = {}
M["strongUpdateURL"][PLATFORM_ANDROID] 	= "www.baidu.com"
M["strongUpdateURL"][PLATFORM_IOS] 		= "www.google.com"

-- 强更新描述
M["strongUpdateDes"] = {}
M["strongUpdateDes"][PLATFORM_ANDROID] 	= "Android我是强更新描述"
M["strongUpdateDes"][PLATFORM_IOS] 		= "IOS我是强更新描述"


-- 重启等级
-- 说明：0->不需要重启 1->程序自动重启 2->用户手动重启
M["restartLevel"] = 0



-- 忽略文件列表
-- 格式
-- M["ignoreFileList"] = 
-- {
-- 	"Image/a.zip",
-- 	"Image/b.zip",
-- 	"c.zip"
-- }
M["ignoreFileList"] = 
{
}

-- 游戏资源文件目录
M["resourceDir"] = lfs.currentdir().."/../../kurumi/"

-- 输出文件目录
M["outputDir"] = lfs.currentdir().."/archives/"

return M
