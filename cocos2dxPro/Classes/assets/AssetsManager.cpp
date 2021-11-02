
#include "AssetsManager.h"
#include "base/ccUTF8.h"



NS_AS_BEGIN

#define TEMP_PACKAGE_SUFFIX     "_temp"

// 临时清单文件名
#define MANIFEST_FILENAME_TEMP			"temp.manifest"
// 缓存清单文件名
#define MANIFEST_FILENAME_CACHE			"cache.manifest"
// 下载远程清单文件名
#define MANIFEST_FILENAME_DOWNLOAD      "download.manifest"



// 文件下载-默认连接超时时间
#define DEFAULT_CONNECTION_TIMEOUT 45
// 文件下载-保存临时文件时后缀
#define TEMP_FILENAME_SUFFIX ".tmp"


const std::string AssetsManager::MANIFEST_ID = "@manifest";



AssetsManager::AssetsManager(const std::string& manifestUrl, const std::string& storagePath, const std::string& platformName)
: m_updateState(State::UNCHECKED)
, m_storagePath("")
, m_cacheManifestPath("")
, m_tempManifestPath("")
, m_manifestUrl(manifestUrl)
, m_localManifest(nullptr)
, m_tempManifest(nullptr)
, m_remoteManifest(nullptr)
, m_maxConcurrentTask(2)
, m_currConcurrentTask(0)
, m_verifyCallback(nullptr)
, m_totalSize(0)
{
    // Init variables
	m_platformName = platformName;
	
    m_fileUtils = cocos2d::FileUtils::getInstance();

	cocos2d::network::DownloaderHints hints =
    {
        static_cast<uint32_t>(m_maxConcurrentTask),
        DEFAULT_CONNECTION_TIMEOUT,
		TEMP_FILENAME_SUFFIX
    };
    m_downloader = std::shared_ptr<cocos2d::network::Downloader>(new cocos2d::network::Downloader(hints));
    m_downloader->onTaskError = std::bind(&AssetsManager::onError, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    m_downloader->onTaskProgress = [this](const cocos2d::network::DownloadTask& task,
                                         int64_t /*bytesReceived*/,
                                         int64_t totalBytesReceived,
                                         int64_t totalBytesExpected)
    {
        this->onProgress(totalBytesExpected, totalBytesReceived, task.requestURL, task.identifier);
    };
    m_downloader->onFileTaskSuccess = [this](const cocos2d::network::DownloadTask& task)
    {
        this->onSuccess(task.requestURL, task.storagePath, task.identifier);
    };
    setStoragePath(storagePath);
    m_cacheManifestPath = m_storagePath + MANIFEST_FILENAME_CACHE;
    m_tempManifestPath = m_tempStoragePath + MANIFEST_FILENAME_TEMP;
	m_downloadManifestPath = m_tempStoragePath + MANIFEST_FILENAME_DOWNLOAD;
}

AssetsManager::~AssetsManager()
{
    m_downloader->onTaskError = (nullptr);
    m_downloader->onFileTaskSuccess = (nullptr);
    m_downloader->onTaskProgress = (nullptr);
    // m_tempManifest could share a ptr with m_remoteManifest or m_localManifest
    if (m_tempManifest != m_localManifest && m_tempManifest != m_remoteManifest)
        CC_SAFE_DELETE(m_tempManifest);
	CC_SAFE_DELETE(m_localManifest);
    CC_SAFE_DELETE(m_remoteManifest);
}

bool AssetsManager::checkUpdate(const LuaFunction& handle)
{
	m_checkCallLuaHandle = handle;
	if (m_updateState != State::UNCHECKED)
	{
		CCLOG("------------->>");
		return false;
	}

	if (!initLocalManifest())
	{
		CCLOG("AssetsManager : No local manifest file found error.\n");
		dispatchCheckUpdateEvent(false, AssetsEventCode::ERROR_NO_LOCAL_MANIFEST);
		return false;
	}

	// 正在检查更新,下载清单文件
	m_updateState = State::CHECK_UPDATE;
	downloadManifest();
	return true;
}

bool AssetsManager::startUpdate(const LuaFunction& handle)
{
	if (m_updateState != State::WAIT_FOR_UPDATE)
	{
		return false;
	}

	m_updateCallLuaHandle = handle;
	m_updateState = State::UPDATING;

	// Clean up before update
	m_failedUnits.clear();
	m_downloadUnits.clear();
	
	if (m_tempManifest)
	{
		// 上一次更新未完成,并且版本号和远程版本号一致,继续之前的更新
		if (m_tempManifest->versionEquals(m_remoteManifest))
		{
			m_tempManifest->genResumeAssetsList(&m_downloadUnits);
			this->batchDownload();
		}
		else
		{
			m_fileUtils->removeDirectory(m_tempStoragePath);
			m_fileUtils->createDirectory(m_tempStoragePath);
			CC_SAFE_DELETE(m_tempManifest);
		}
	}

	if (m_tempManifest == NULL)
	{
		m_tempManifest = m_remoteManifest;

		std::unordered_map<std::string, Manifest::AssetDiff> diff_map = m_localManifest->genDiff(m_remoteManifest);
		if (diff_map.size() == 0)
		{
			updateSucceed();
		}
		else
		{
			std::string packageUrl = m_remoteManifest->getPackageUrl();

			// Preprocessing local files in previous version and creating download folders
			for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
			{
				Manifest::AssetDiff diff = it->second;
				if (diff.type != Manifest::DiffType::DELETED)
				{
					std::string path = diff.asset.path;
					DownloadUnit unit;
					unit.customId = it->first;
					unit.srcUrl = packageUrl + path;
					unit.storagePath = m_tempStoragePath + path;
					unit.downloadSize = diff.asset.downloadSize;
					unit.fileSize = diff.asset.fileSize;
					m_downloadUnits.emplace(unit.customId, unit);
					m_tempManifest->setAssetDownloadState(it->first, Manifest::DownloadState::UNSTARTED);
				}
			}
			this->savePercentFile();
			this->batchDownload();
		}
	}

	return true;
}

void AssetsManager::repair()
{
	Utils::removeFile(m_cacheManifestPath);

	m_fileUtils->removeDirectory(m_storagePath);
	m_fileUtils->createDirectory(m_storagePath);
	// 清空临时目录
	m_fileUtils->removeDirectory(m_tempStoragePath);
	m_fileUtils->createDirectory(m_tempStoragePath);
}

bool AssetsManager::initLocalManifest()
{
	CC_SAFE_DELETE(m_localManifest);

	// 读取包内的清单文件
	m_localManifest = new (std::nothrow) Manifest(m_manifestUrl, m_platformName);
	if (!m_localManifest->isLoaded())
	{
		CC_SAFE_DELETE(m_localManifest);
		return false;
	}

	// 读取之前更新缓存下来的清单文件
	Manifest *cachedManifest = new (std::nothrow) Manifest(m_cacheManifestPath, m_platformName);
	if (cachedManifest->isLoaded())
	{
		// 包内的版本号比缓存版本号还要新,之前更新的文件都可以删除了
		if (m_localManifest->versionGreater(cachedManifest))
		{
			repair();
			CC_SAFE_DELETE(cachedManifest);
		}
		else
		{
			CC_SAFE_DELETE(m_localManifest);
			m_localManifest = cachedManifest;
		}
	}
	else
	{
		if (m_fileUtils->isFileExist(m_cacheManifestPath))
		{
			repair();
		}
		CC_SAFE_DELETE(cachedManifest);
	}


	// 存在临时清单文件,表示上一次更新未完成
	if (m_fileUtils->isFileExist(m_tempManifestPath))
	{
		m_tempManifest = new (std::nothrow) Manifest(m_tempManifestPath, m_platformName);

		if (m_tempManifest->isLoaded())
		{
			// 包内的版本号比上一次正在更新的版本号还要新,之前更新的文件都可以删除了
			if (m_localManifest->versionGreater(m_tempManifest))
			{
				repair();
			}
		}
		else
		{
			CC_SAFE_DELETE(m_tempManifest);
		}
	}

	return true;
}

void AssetsManager::downloadManifest()
{
	std::string manifestUrl = m_localManifest->getManifestFileUrl();
	if (manifestUrl.size() > 0)
	{
		Utils::removeFile(m_downloadManifestPath + TEMP_FILENAME_SUFFIX);
		Utils::removeFile(m_downloadManifestPath);
		m_downloader->createDownloadFileTask(manifestUrl, m_downloadManifestPath, MANIFEST_ID);
	}
	else
	{
		CCLOG("AssetsManager : No manifest file found, check update failed\n");
		m_updateState = State::UNCHECKED;
		dispatchCheckUpdateEvent(false, AssetsEventCode::ERROR_DOWNLOAD_MANIFEST);
	}
}

void AssetsManager::parseManifest()
{
	CC_SAFE_DELETE(m_remoteManifest);

	m_remoteManifest = new Manifest(m_downloadManifestPath, m_platformName);

	if (!m_remoteManifest->isLoaded())
	{
		CCLOG("AssetsManager : Error parsing manifest file, %s", m_downloadManifestPath.c_str());
		m_updateState = State::UNCHECKED;
		dispatchCheckUpdateEvent(false, AssetsEventCode::ERROR_PARSE_MANIFEST);
	}
	else
	{
		// 需要强更新
		if (m_localManifest->isNeedStrongUpdate(m_remoteManifest))
		{
			m_updateState = State::WAIT_FOR_UPDATE;
			m_fileUtils->removeDirectory(m_tempStoragePath);
			dispatchCheckUpdateEvent(true, AssetsEventCode::NEED_STRONG_UPDATE);
		}
		else
		{
			if (m_localManifest->versionGreater(m_remoteManifest))
			{
				// 已经是最新版本了
				m_updateState = State::UP_TO_DATE;
				m_fileUtils->removeDirectory(m_tempStoragePath);
				dispatchCheckUpdateEvent(true, AssetsEventCode::ALREADY_UP_TO_DATE);
			}
			else
			{
				// 版本号不一样,可能需要更新
				// 开始计算需要更新的文件大小
				if (calculateUpdateFileSize())
				{
					// 需要更新
					m_updateState = State::WAIT_FOR_UPDATE;
					dispatchCheckUpdateEvent(true, AssetsEventCode::NEW_VERSION_FOUND);
				}
				else
				{
					// 对比差异后发现没有需要更新的文件,仅仅是版本号不一样
					dispatchCheckUpdateEvent(true, AssetsEventCode::ALREADY_UP_TO_DATE);
				}
			}
		}
	}
	Utils::removeFile(m_downloadManifestPath);
}

bool AssetsManager::calculateUpdateFileSize()
{
	m_totalSize = 0;

	if (m_tempManifest && m_tempManifest->isLoaded() && m_tempManifest->versionEquals(m_remoteManifest))
	{
		DownloadUnits downloadUnits;
		m_tempManifest->genResumeAssetsList(&downloadUnits);

		for (auto& it : downloadUnits)
		{
			m_totalSize += it.second.fileSize;
		}
	}
	else
	{
		std::unordered_map<std::string, Manifest::AssetDiff> diff_map = m_localManifest->genDiff(m_remoteManifest);

		bool add = false;
		// Preprocessing local files in previous version and creating download folders
		for (auto it = diff_map.begin(); it != diff_map.end(); ++it)
		{
			Manifest::AssetDiff diff = it->second;
			if (diff.type != Manifest::DiffType::DELETED)
			{
				m_totalSize = m_totalSize + diff.asset.fileSize;
				add = true;
			}
		}

		if (!add)
		{
			return false;
		}
	}
	return true;
}

const Manifest* AssetsManager::getLocalManifest() const
{
    return m_localManifest;
}

const Manifest* AssetsManager::getRemoteManifest() const
{
    return m_remoteManifest;
}

const std::string& AssetsManager::getStoragePath() const
{
    return m_storagePath;
}

void AssetsManager::setVerifyLuaCallback(const LuaFunction& handle)
{
	m_verifyLuaHandle = std::move(handle);
	this->setVerifyCallback([this](const std::string& path, Manifest::Asset asset)->bool
	{
		m_verifyLuaHandle.ppush();
		m_verifyLuaHandle.pusharg(path.c_str());
		m_verifyLuaHandle.pushusertype(&asset, "assets::ManifestAsset");
		m_verifyLuaHandle.pcall(1);

		return m_verifyLuaHandle.retbool();
	});
}

void AssetsManager::setStoragePath(const std::string& storagePath)
{
    m_storagePath = storagePath;
	Utils::adjustPath(m_storagePath);
    m_fileUtils->createDirectory(m_storagePath);
    
    m_tempStoragePath = m_storagePath;
    m_tempStoragePath.insert(m_storagePath.size() - 1, TEMP_PACKAGE_SUFFIX);
    m_fileUtils->createDirectory(m_tempStoragePath);
}

void AssetsManager::decompressDownloadedZip(const std::string &customId, const std::string &storagePath)
{
    struct AsyncData
    {
        std::string customId;
        std::string zipFile;
		std::string error;
        bool succeed;
    };
    
    AsyncData* asyncData = new AsyncData;
    asyncData->customId = customId;
    asyncData->zipFile = storagePath;
    asyncData->succeed = false;
    
    std::function<void(void*)> decompressFinished = [this](void* param) {
        auto dataInner = reinterpret_cast<AsyncData*>(param);
        if (dataInner->succeed)
        {
            fileSuccess(dataInner->customId, dataInner->zipFile);
        }
        else
        {
			std::string errorMsg = cocos2d::StringUtils::format("Unable to decompress file : %s\nerror: %s", dataInner->zipFile.c_str(), dataInner->error.c_str());

			Utils::removeFile(dataInner->zipFile);
            fileError(dataInner->customId);
			dispatchUpdateEvent(false, AssetsEventCode::ERROR_DECOMPRESS, errorMsg);
        }
        delete dataInner;
    };
	cocos2d::AsyncTaskPool::getInstance()->enqueue(cocos2d::AsyncTaskPool::TaskType::TASK_OTHER, std::move(decompressFinished), (void*)asyncData, [this, asyncData]() {
        // Decompress all compressed files
        if (Utils::decompressZip(asyncData->zipFile, asyncData->error))
        {
            asyncData->succeed = true;
        }
		Utils::removeFile(asyncData->zipFile);
    });
}

void AssetsManager::savePercentFile()
{
	m_tempManifest->saveToFile(m_tempManifestPath);
}

void AssetsManager::updateSucceed()
{
	savePercentFile();

    // Every thing is correctly downloaded, do the following
    // 1. rename temporary manifest to valid manifest
    std::string tempFileName = MANIFEST_FILENAME_TEMP;
    std::string fileName = MANIFEST_FILENAME_CACHE;
    m_fileUtils->renameFile(m_tempStoragePath, tempFileName, fileName);

    // 2. merge temporary storage path to storage path so that temporary version turns to cached version
    if (m_fileUtils->isDirectoryExist(m_tempStoragePath))
    {
        // Merging all files in temp storage path to storage path
        std::vector<std::string> files;
        Utils::listFilesRecursively(m_tempStoragePath, &files);
        int baseOffset = (int)m_tempStoragePath.length();
        std::string relativePath, dstPath;
        for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
        {
            relativePath.assign((*it).substr(baseOffset));
            dstPath.assign(m_storagePath + relativePath);
            // Create directory
            if (relativePath.back() == '/')
            {
                m_fileUtils->createDirectory(dstPath);
            }
            // Copy file
            else
            {
				Utils::removeFile(dstPath);
                m_fileUtils->renameFile(*it, dstPath);
            }
        }
        // Remove temp storage path
        m_fileUtils->removeDirectory(m_tempStoragePath);
    }
    // 3. swap the localManifest
    CC_SAFE_DELETE(m_localManifest);
    m_localManifest = m_remoteManifest;
    m_localManifest->setManifestRoot(m_storagePath);
    m_remoteManifest = nullptr;


    // 5. Set update state
    m_updateState = State::UP_TO_DATE;
	dispatchUpdateEvent(true, AssetsEventCode::SUCCESS, "Update succeeded");
}

// 获取需要更新的总大小
double AssetsManager::getTotalSize()
{
	return (double)m_totalSize;
}

// 获取已经下载的大小
double AssetsManager::getDownloadSize()
{
	if (m_percentFileMap.empty())
	{
		return 0.0;
	}

	int64_t curSize = 0;
	unsigned int totalSize = 0;
	for (auto &it : m_percentFileMap)
	{
		curSize += it.second.curSize;
	}

	return (double)curSize;
}

/** @brief 获取更新进度
*/
float AssetsManager::getUpdatePercent()
{
	auto cur = getDownloadSize();
	auto total = getTotalSize();

	if (total > 0.0f)
	{
		return float(cur / total);
	}

	if (m_updateState == State::UP_TO_DATE)
	{
		return 1.0f;
	}
	return 0.0f;
}

void AssetsManager::onError(const cocos2d::network::DownloadTask& task,
	int errorCode,
	int errorCodeInternal,
	const std::string& errorStr)
{
	CCLOG("\n\n");
	CCLOG("requestURL : %s", task.requestURL.c_str());
	CCLOG("storagePath: %s", task.storagePath.c_str());
	CCLOG("error	  : %s", errorStr.c_str());
	CCLOG("errorCode  : %d", errorCode);
	CCLOG("errorCodeInternal: %d", errorCodeInternal);

	if (task.identifier == MANIFEST_ID)
	{
		dispatchCheckUpdateEvent(false, AssetsEventCode::ERROR_DOWNLOAD_MANIFEST);
		m_updateState = State::UNCHECKED;
	}
	else
	{
		fileError(task.identifier);

		std::string err = cocos2d::StringUtils::format("url: %s\nerrorCode: %d \nerrorCodeInternal: %d \nerrorStr: %s \n", task.requestURL.c_str(), errorCode, errorCodeInternal, errorStr.c_str());
		dispatchUpdateEvent(false, AssetsEventCode::ERROR_DOWNLOAD, err);
	}
}

void AssetsManager::onProgress(int64_t total, int64_t downloaded, const std::string& /*url*/, const std::string &customId)
{
	if (customId == MANIFEST_ID)
	{
		//float percent = 100 * downloaded / total;
		return;
	}
	else
	{
		// 更新总进度
		auto it_percent = m_percentFileMap.find(customId);
		if (it_percent != m_percentFileMap.end())
		{
			it_percent->second.curSize = downloaded;
			it_percent->second.totalSize = total;
			it_percent->second.state = Manifest::DownloadState::DOWNLOADING;
		}

		m_tempManifest->setAssetDownloadSize(customId, downloaded);
	}
}

void AssetsManager::onSuccess(const std::string &/*srcUrl*/, const std::string &storagePath, const std::string &customId)
{
	if (customId == MANIFEST_ID)
	{
		parseManifest();
	}
	else
	{
		// 更新总进度
		auto it_percent = m_percentFileMap.find(customId);
		if (it_percent != m_percentFileMap.end())
		{
			it_percent->second.curSize = it_percent->second.totalSize;
			it_percent->second.state = Manifest::DownloadState::SUCCESSED;
		}

		bool ok = true;
		auto &assets = m_remoteManifest->getAssets();
		auto assetIt = assets.find(customId);
		if (assetIt != assets.end())
		{
			Manifest::Asset asset = assetIt->second;
			if (m_verifyCallback != nullptr)
			{
				ok = m_verifyCallback(storagePath, asset);
			}
		}

		if (ok)
		{
			bool compressed = assetIt != assets.end() ? assetIt->second.compressed : false;
			if (compressed)
			{
				decompressDownloadedZip(customId, storagePath);
			}
			else
			{
				fileSuccess(customId, storagePath);
			}
		}
		else
		{
			Utils::removeFile(storagePath);
			fileError(customId);

			auto err = cocos2d::StringUtils::format("Asset file verification failed after downloaded, file: %s", customId.c_str());
			dispatchUpdateEvent(false, AssetsEventCode::ERROR_VERIF, err);
		}
	}
}

void AssetsManager::fileError(const std::string& identifier)
{
	// 更新总进度
	auto it_percent = m_percentFileMap.find(identifier);
	if (it_percent != m_percentFileMap.end())
	{
		it_percent->second.curSize = it_percent->second.totalSize;
		it_percent->second.state = Manifest::DownloadState::SUCCESSED;
	}

    auto unitIt = m_downloadUnits.find(identifier);
    // Found unit and add it to failed units
    if (unitIt != m_downloadUnits.end())
    {        
        DownloadUnit unit = unitIt->second;
        m_failedUnits.emplace(unit.customId, unit);
    }
	m_tempManifest->setAssetDownloadSize(identifier, 0);
    m_tempManifest->setAssetDownloadState(identifier, Manifest::DownloadState::UNSTARTED);
    
    m_currConcurrentTask = MAX(0, m_currConcurrentTask-1);
    queueDowload();
}

void AssetsManager::fileSuccess(const std::string &customId, const std::string &storagePath)
{
    // Set download state to SUCCESSED
    m_tempManifest->setAssetDownloadState(customId, Manifest::DownloadState::SUCCESSED);
    
    auto unitIt = m_failedUnits.find(customId);
    // Found unit and delete it
    if (unitIt != m_failedUnits.end())
    {
        // Remove from failed units list
        m_failedUnits.erase(unitIt);
    }
        
    m_currConcurrentTask = MAX(0, m_currConcurrentTask-1);
    queueDowload();
}

void AssetsManager::batchDownload()
{
	m_percentFileMap.clear();
    m_downloadQueue.clear();

	TaskPercentData percentData;
    for(auto iter : m_downloadUnits)
    {
        const DownloadUnit& unit = iter.second;
        
        m_downloadQueue.push_back(iter.first);

		percentData.curSize = (unsigned int)unit.downloadSize;
		percentData.state = Manifest::UNSTARTED;
		percentData.totalSize = unit.fileSize;
		m_percentFileMap.insert(std::make_pair(iter.first, percentData));
    }

    queueDowload();
}

void AssetsManager::queueDowload()
{
	if (m_downloadQueue.empty() && m_currConcurrentTask <= 0)
	{
		this->onDownloadUnitsFinished();
		return;
	}

    while (m_currConcurrentTask < m_maxConcurrentTask && m_downloadQueue.size() > 0)
    {
        std::string key = m_downloadQueue.back();
        m_downloadQueue.pop_back();
        
        m_currConcurrentTask++;
        DownloadUnit& unit = m_downloadUnits[key];
        m_fileUtils->createDirectory(Utils::getBasename(unit.storagePath));
        m_downloader->createDownloadFileTask(unit.srcUrl, unit.storagePath, unit.customId);
        
        m_tempManifest->setAssetDownloadState(key, Manifest::DownloadState::DOWNLOADING);
    }

	savePercentFile();
}

void AssetsManager::onDownloadUnitsFinished()
{
	savePercentFile();

	// 有些文件下载失败
    if (m_failedUnits.size() > 0)
    {
        m_updateState = State::WAIT_FOR_UPDATE;
		dispatchUpdateEvent(true, AssetsEventCode::ERROR_DOWNLOAD, "Resource download failed");
    }
    else if (m_updateState == State::UPDATING)
    {
        updateSucceed();
    }
	else
	{
		CC_ASSERT(false);
	}
}

void AssetsManager::dispatchCheckUpdateEvent(bool success, AssetsEventCode code)
{
	if (m_checkCallLuaHandle.isvalid())
	{
		m_checkCallLuaHandle.ppush();
		m_checkCallLuaHandle.pusharg(success);
		m_checkCallLuaHandle.pusharg((int)code);
		m_checkCallLuaHandle.pcall();
	}
}

void AssetsManager::dispatchUpdateEvent(bool finish, AssetsEventCode code, const std::string& msg)
{
	if (m_updateCallLuaHandle.isvalid())
	{
		m_updateCallLuaHandle.ppush();
		m_updateCallLuaHandle.pusharg(finish);
		m_updateCallLuaHandle.pusharg((int)code);
		m_updateCallLuaHandle.pusharg(msg.c_str());
		m_updateCallLuaHandle.pcall();
	}
}


NS_AS_END