require "lfs"

--get filename  
function getFileName(str)  
    local idx = str:match(".+()%.%w+$")  
    if(idx) then  
        return str:sub(1, idx-1)  
    else  
        return str  
    end  
end  
  
--get file postfix  
function getExtension(str)  
    return str:match(".+%.(%w+)$")  
end  
  
local filesTab = {}

function fun(rootpath)  
    for entry in lfs.dir(rootpath) do  
        if entry ~= '.' and entry ~= '..' then  
            local path = rootpath .. '/' .. entry  
            local attr = lfs.attributes(path)  
            -- local filename = getFileName(entry)  
  
            if attr.mode ~= 'directory' then
            	if attr.mode == "file" then
            		table.insert(filesTab, path)
            	end
            else
                -- print(filename .. '\t' .. attr.mode)  
                fun(path)  
            end  
        end  
    end  
end  

local function read_files(fileName)
    local f = assert(io.open(fileName,'rb'))
    local content = f:read("*all")f:close()
    return content
end 

local function write_content( fileName,content )
    local  f = assert(io.open(fileName,'wb'))
    f:write(content)
    f:close()
end

 function length_of_file(filename)
  local fh = assert(io.open(filename, "rb"))
  local len = assert(fh:seek("end"))
  fh:close()
  return len
end

function file_isExist(filename)
	local f = io.open(filename,"r")
	if f == nil then
		return false
	end
	f:close()
	return true
end


--------------------------------------------------------------------------
function doit()
	if not file_isExist("config.lua") then
		print("Error：the 'config.lua' does not exist")
	end
    local config = require("config")
    
    local rootDir = config["resourceDir"]
    print("ResourceDir: ", rootDir)
    
    -- 获取目录所有文件列表
    fun(rootDir)  
    
    
    local assetsTab = {}
    -- 需要解压的压缩文件列表
    local compressedFileList = config["compressedFileList"]
	-- 忽略文件列表
	local ignoreFileList = config["ignoreFileList"]
    
    local md5 = MD5:new_local()
    
    local function isCompressedFileList(filename)
        for k,v in pairs(compressedFileList) do
            if v == filename then
                return true
            end
        end
        return false
    end
    
	local function isIgnoreFileList(filename)
        for k,v in pairs(ignoreFileList) do
            if v == filename then
                return true
            end
        end
        return false
    end
    
    -- 计算文件MD5值
    for k,v in pairs(filesTab) do
    
        local filename = string.sub(v, #rootDir + 2, -1)
		
		if not isIgnoreFileList(filename) then
			local fileContent = read_files(v)
			md5:reset()
			md5:update(fileContent, string.len(fileContent))
        
			assetsTab[filename] = {}
			assetsTab[filename]["md5"] = md5:toString()
            assetsTab[filename]["fileSize"] = length_of_file(v)
    
			if getExtension(filename) == "zip" and isCompressedFileList(filename) then
				assetsTab[filename]["compressed"] = true
			end    
        end
    end
    
    local projectManifest = {}
    local versionManifest = {}
    
    projectManifest["packageUrl"]           = config["packageUrl"]
    projectManifest["remoteManifestUrl"]    = config["remoteManifestUrl"]
    projectManifest["remoteVersionUrl"]     = config["remoteVersionUrl"]
    projectManifest["version"]              = config["version"]
    projectManifest["engineVersion"]        = config["engineVersion"]
    projectManifest["searchPaths"]          = config["searchPaths"]
    projectManifest["strongUpdateVer"]      = config["strongUpdateVer"]
    projectManifest["strongUpdateURL"]      = config["strongUpdateURL"]
    projectManifest["strongUpdateDes"]      = config["strongUpdateDes"]
    projectManifest["updateDescription"]    = config["updateDescription"]
    projectManifest["restartLevel"]         = config["restartLevel"]
    
    versionManifest["packageUrl"]           = config["packageUrl"]
    versionManifest["remoteManifestUrl"]    = config["remoteManifestUrl"]
    versionManifest["remoteVersionUrl"]     = config["remoteVersionUrl"]
    versionManifest["version"]              = config["version"]
    versionManifest["engineVersion"]        = config["engineVersion"]
    versionManifest["searchPaths"]          = config["searchPaths"]
    versionManifest["strongUpdateVer"]      = config["strongUpdateVer"]
    versionManifest["strongUpdateURL"]      = config["strongUpdateURL"]
    versionManifest["strongUpdateDes"]      = config["strongUpdateDes"]
    versionManifest["updateDescription"]    = config["updateDescription"]
    versionManifest["restartLevel"]         = config["restartLevel"]

    projectManifest["assets"] = assetsTab
    
    local json = require("json")
    
    local projectJson = json.encode(projectManifest)
    local versionJson = json.encode(versionManifest)

    write_content("project_dev.manifest", prettyJson(projectJson))
    write_content("version_dev.manifest", prettyJson(versionJson))
end