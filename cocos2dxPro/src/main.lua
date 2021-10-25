
cc.FileUtils:getInstance():setPopupNotify(false)

require "config"
require "cocos.init"

local function main()

    local writablePath = cc.FileUtils:getInstance():getWritablePath()
    local storagePath = writablePath .. "new_version"

    local searchPaths = cc.FileUtils:getInstance():getSearchPaths()

    local newSearchPaths = {}
    newSearchPaths[1] = storagePath.."/src/"
    newSearchPaths[2] = storagePath.."/res/"

    for k,v in pairs(searchPaths) do
        newSearchPaths[k + 2] = v
    end
    cc.FileUtils:getInstance():setSearchPaths(newSearchPaths)

    require("app.MyApp"):create():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
