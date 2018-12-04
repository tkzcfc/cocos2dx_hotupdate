
local SecondScene = class("SecondScene", cc.load("mvc").ViewBase)

function SecondScene:onCreate()

    self.uiPage = require("SecondScene").create(function (path, node, funcName)
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
end

return SecondScene
