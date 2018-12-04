
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("src/")
cc.FileUtils:getInstance():addSearchPath("res/")

local cacheLoadedTab = {}
local cachePreloadedTab = {}
local gAppInstance = nil

function restartApp(sceneName)
	for k,v in pairs(package.loaded) do
		if not cacheLoadedTab[k] then
			package.loaded[k] = nil
			print("remove loaded:", k)
		end
	end

	for k,v in pairs(package.preload) do
		if not cachePreloadedTab[k] then
			package.preload[k] = nil
			print("remove preload:", k)
		end
	end

    gAppInstance:run(sceneName)
end

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
	
	cacheLoadedTab = {}
	for k,v in pairs(package.loaded) do
		cacheLoadedTab[k] = true
	end
	
	cachePreloadedTab = {}
	for k,v in pairs(package.preload) do
		cachePreloadedTab[k] = true
	end

	gAppInstance = require("app.MyApp"):create()
    gAppInstance:run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
