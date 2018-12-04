-- 平台定义
PLATFORM_ANDROID = "android"
PLATFORM_IOS 	 = "ios"
PLATFORM_WINDOWS = "windows"
PLATFORM_MAC 	 = "mac"
PLATFORM_LINUX 	 = "linux"



local M = {}

-- 要下载具体内容的地址
M["packageUrl"] = "http://www.kurumi.xin:8080/download/ResourceDir/"

-- 远程的配置清单文件地址
M["remoteManifestUrl"] = "http://www.kurumi.xin:8080/download/project_dev.manifest"

-- 远程版本文件地址
M["remoteVersionUrl"] = "http://www.kurumi.xin:8080/download/version_dev.manifest"

-- 资源版本（重要，关系到是否更不更新）
M["version"] = "0.0.0"

-- 更新描述
M["updateDescription"] = [[1:修复bug
2:增加功能
]]

-- 强更新版本(如果客户端版本小于当前版本，则客户端进行弹框提示，用户确认跳转至新版本下载地址)
M["strongUpdateVer"] = {}
-- 平台PLATFORM_ANDROID强更新版本
M["strongUpdateVer"][PLATFORM_ANDROID] 	= 0
-- 平台PLATFORM_IOS强更新版本
M["strongUpdateVer"][PLATFORM_IOS] 		= 0
--...

-- 强更新下载地址
M["strongUpdateURL"] = {}
M["strongUpdateURL"][PLATFORM_ANDROID] 	= "www.baidu.com"
M["strongUpdateURL"][PLATFORM_IOS] 		= "www.baidu.com"

-- 强更新描述
M["strongUpdateDes"] = {}
M["strongUpdateDes"][PLATFORM_ANDROID] 	= "我是强更新描述"
M["strongUpdateDes"][PLATFORM_IOS] 		= "我是强更新描述"


-- 重启等级
-- 说明：0->不需要重启 1->程序自动重启 2->用户手动重启
M["restartLevel"] = 0


-- 引擎版本（无关紧要）
M["engineVersion"] = "3.x dev"

-- 搜索路径
-- 格式
-- M["searchPaths"] = 
-- {
-- 	"res/b",
-- 	"res/img",
-- }
M["searchPaths"] = {}


-- 需要解压的压缩文件列表(在下载资源完毕后需要解压的zip文件)
-- 格式
-- M["compressedFileList"] = 
-- {
-- 	"Image/a.zip",
-- 	"Image/b.zip",
-- 	"c.zip"
-- }
M["compressedFileList"] = {}

-- 忽略文件列表 (必须忽略客户端打包进去的project_dev.manifest文件)
-- 格式
-- M["ignoreFileList"] = 
-- {
-- 	"Image/a.zip",
-- 	"Image/b.zip",
-- 	"c.zip"
-- }
M["ignoreFileList"] = 
{
	"res/version/project.manifest"
}

-- 资源文件目录
M["resourceDir"] = lfs.currentdir().."\\ResourceDir"

return M
