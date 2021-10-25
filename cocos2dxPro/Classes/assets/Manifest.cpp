
#include "Manifest.h"
#include "Utils.h"
#include "external/json/prettywriter.h"
#include "external/json/stringbuffer.h"

#include <fstream>
#include <stdio.h>

NS_AS_BEGIN

#define KEY_VERSION             "version"
#define KEY_PACKAGE_URL         "packageUrl"
#define KEY_MANIFEST_URL        "remoteManifestUrl"
#define KEY_ASSETS              "assets"



#define KEY_PATH                "path"
#define KEY_MD5                 "md5"
#define KEY_COMPRESSED          "compressed"
#define KEY_DOWNLOAD_SIZE	    "downloadSize"
#define KEY_DOWNLOAD_STATE      "downloadState"

 // 强更新版本
#define KEY_STRONG_UPDATE_VER	"strongUpdateVer"
 // 强更新地址
#define KEY_STRONG_UPDATE_URL   "strongUpdateURL"
// 强更新描述
#define KEY_STRONG_UPDATE_DES	"strongUpdateDes"
// 文件大小
#define KEY_RESOURCE_FILE_SIZE	"fileSize"
// 更新描述
#define KEY_UPDATE_DESCRIPTION	"updateDescription"
// 重启等级
#define KEY_RESTART_LEVEL		"restartLevel"
// 散文件模式
#define KEY_LOOSE_FILE_MODE		"looseFileMode"

using namespace cocos2d;

static int cmpVersion(const std::string& v1, const std::string& v2)
{
    int i;
    int oct_v1[3] = {0}, oct_v2[3] = {0};
    int filled1 = std::sscanf(v1.c_str(), "%d.%d.%d", &oct_v1[0], &oct_v1[1], &oct_v1[2]);
    int filled2 = std::sscanf(v2.c_str(), "%d.%d.%d", &oct_v2[0], &oct_v2[1], &oct_v2[2]);
    
    if (filled1 == 0 || filled2 == 0)
    {
        return strcmp(v1.c_str(), v2.c_str());
    }
    for (i = 0; i < 3; i++)
    {
        if (oct_v1[i] > oct_v2[i])
            return 1;
        else if (oct_v1[i] < oct_v2[i])
            return -1;
    }
    return 0;
}

Manifest::Manifest(const std::string& manifestUrl, const std::string& platform)
: m_loaded(false)
, m_manifestRoot("")
, m_remoteManifestUrl("")
, m_version("")
, m_strongUpdateVer(0)
, m_restartLevel(0)
, m_strongUpdateURL("")
, m_strongUpdateDescription("")
, m_looseFileMode(true)
{
	m_platform = platform;

    if (manifestUrl.size() > 0)
        parse(manifestUrl);
}

bool Manifest::loadJson(const std::string& url)
{
    clear();
    std::string content;
    if (FileUtils::getInstance()->isFileExist(url))
    {
        // Load file content
        content = FileUtils::getInstance()->getStringFromFile(url);
        
        if (content.size() == 0)
        {
            CCLOG("Fail to retrieve local file content: %s\n", url.c_str());
			return false;
        }
        else
        {
            // Parse file with rapid json
            m_json.Parse<0>(content.c_str());
            // Print error
            if (m_json.HasParseError()) {
                size_t offset = m_json.GetErrorOffset();
                if (offset > 0)
                    offset--;
                std::string errorSnippet = content.substr(offset, 10);
                CCLOG("File parse error %d at <%s>\n", m_json.GetParseError(), errorSnippet.c_str());
				return false;
            }
			return true;
        }
    }
	return false;
}

void Manifest::parse(const std::string& manifestUrl)
{
	m_loaded = false;

    loadJson(manifestUrl);
	
    if (!m_json.HasParseError() && m_json.IsObject())
    {
        // Register the local manifest root
        size_t found = manifestUrl.find_last_of("/\\");
        if (found != std::string::npos)
        {
            m_manifestRoot = manifestUrl.substr(0, found+1);
        }
        loadManifest(m_json);

		updateExtData();

		m_loaded = true;
    }
}

bool Manifest::isLoaded() const
{
    return m_loaded;
}

bool Manifest::versionEquals(const Manifest *b) const
{
	return m_version == b->getVersion();
}

bool Manifest::versionGreater(const Manifest *b) const
{
    std::string localVersion = getVersion();
    std::string bVersion = b->getVersion();
    bool greater = cmpVersion(localVersion, bVersion) >= 0;
    return greater;
}

// 获取差异文件
std::unordered_map<std::string, Manifest::AssetDiff> Manifest::genDiff(const Manifest *b) const
{
    std::unordered_map<std::string, AssetDiff> diff_map;
    const std::unordered_map<std::string, Asset> &bAssets = b->getAssets();
    
	// 散文件更新
	if (b->isLooseFileMode())
	{
		std::string key;
		Asset valueA;
		Asset valueB;

		std::unordered_map<std::string, Asset>::const_iterator valueIt, it;
		for (it = m_assets.begin(); it != m_assets.end(); ++it)
		{
			key = it->first;
			valueA = it->second;

			// Deleted
			valueIt = bAssets.find(key);
			if (valueIt == bAssets.cend()) {
				AssetDiff diff;
				diff.asset = valueA;
				diff.type = DiffType::DELETED;
				diff_map.emplace(key, diff);
				continue;
			}

			// Modified
			valueB = valueIt->second;
			if (valueA.md5 != valueB.md5) {
				AssetDiff diff;
				diff.asset = valueB;
				diff.type = DiffType::MODIFIED;
				diff_map.emplace(key, diff);
			}
		}

		for (it = bAssets.begin(); it != bAssets.end(); ++it)
		{
			key = it->first;
			valueB = it->second;

			// Added
			valueIt = m_assets.find(key);
			if (valueIt == m_assets.cend()) {
				AssetDiff diff;
				diff.asset = valueB;
				diff.type = DiffType::ADDED;
				diff_map.emplace(key, diff);
			}
		}
	}
	else
	{
		auto from = this->getVersion();
		auto to = b->getVersion();

		Utils::replace(from, ".", "_");
		Utils::replace(to, ".", "_");

		// 整包差异更新
		std::string updateFile = cocos2d::StringUtils::format("%s_to_%s.zip", from.c_str(), to.c_str());

		auto it = bAssets.find(updateFile);
		if (it != bAssets.cend())
		{
			AssetDiff diff;
			diff.asset = it->second;
			diff.type = DiffType::ADDED;
			diff_map.emplace(it->first, diff);
		}
	}
    return diff_map;
}

void Manifest::genResumeAssetsList(DownloadUnits *units) const
{
    for (auto it = m_assets.begin(); it != m_assets.end(); ++it)
    {
        Asset asset = it->second;
        
        if (asset.downloadState != DownloadState::SUCCESSED && asset.downloadState != DownloadState::UNMARKED)
        {
            DownloadUnit unit;
            unit.customId = it->first;
            unit.srcUrl = m_packageUrl + asset.path;
            unit.storagePath = m_manifestRoot + asset.path;
            unit.downloadSize = asset.downloadSize;
			unit.fileSize = asset.fileSize;
            units->emplace(unit.customId, unit);
        }
    }
}

const std::string& Manifest::getPackageUrl() const
{
    return m_packageUrl;
}

const std::string& Manifest::getManifestFileUrl() const
{
    return m_remoteManifestUrl;
}

const std::string& Manifest::getVersion() const
{
    return m_version;
}

const std::unordered_map<std::string, Manifest::Asset>& Manifest::getAssets() const
{
    return m_assets;
}

void Manifest::setAssetDownloadState(const std::string &key, const Manifest::DownloadState &state)
{
    auto valueIt = m_assets.find(key);
    if (valueIt != m_assets.end())
    {
        valueIt->second.downloadState = state;
        
        // Update json object
        if(m_json.IsObject())
        {
            if ( m_json.HasMember(KEY_ASSETS) )
            {
                rapidjson::Value &assets = m_json[KEY_ASSETS];
                if (assets.IsObject())
                {
                    if (assets.HasMember(key.c_str()))
                    {
                        rapidjson::Value &entry = assets[key.c_str()];
                        if (entry.HasMember(KEY_DOWNLOAD_STATE) && entry[KEY_DOWNLOAD_STATE].IsInt())
                        {
                            entry[KEY_DOWNLOAD_STATE].SetInt((int) state);
                        }
                        else
                        {
                            entry.AddMember<int>(KEY_DOWNLOAD_STATE, (int)state, m_json.GetAllocator());
                        }
                    }
                }
            }
        }
    }
}

void Manifest::setAssetDownloadSize(const std::string &key, int64_t downloadSize)
{
	auto valueIt = m_assets.find(key);
	if (valueIt != m_assets.end())
	{
		valueIt->second.downloadSize = downloadSize;

		// Update json object
		if (m_json.IsObject())
		{
			if (m_json.HasMember(KEY_ASSETS))
			{
				rapidjson::Value &assets = m_json[KEY_ASSETS];
				if (assets.IsObject())
				{
					if (assets.HasMember(key.c_str()))
					{
						rapidjson::Value &entry = assets[key.c_str()];
						if (entry.HasMember(KEY_DOWNLOAD_SIZE) && entry[KEY_DOWNLOAD_SIZE].IsInt64())
						{
							entry[KEY_DOWNLOAD_SIZE].SetInt64(downloadSize);
						}
						else
						{
							entry.AddMember<int64_t>(KEY_DOWNLOAD_SIZE, downloadSize, m_json.GetAllocator());
						}
					}
				}
			}
		}
	}
}

void Manifest::clear()
{
    if (m_loaded)
    {  
		m_remoteManifestUrl = "";
        m_version = "";
        m_assets.clear();
        m_loaded = false;
    }
	m_strongUpdateVer = 0;
	m_strongUpdateURL = "";
	m_strongUpdateDescription = "";
	m_looseFileMode = true;
}

Manifest::Asset Manifest::parseAsset(const std::string &path, const rapidjson::Value &json)
{
    Asset asset;
    asset.path = path;
	
    if ( json.HasMember(KEY_MD5) && json[KEY_MD5].IsString() )
    {
        asset.md5 = json[KEY_MD5].GetString();
    }
    else asset.md5 = "";
    
    if ( json.HasMember(KEY_PATH) && json[KEY_PATH].IsString() )
    {
        asset.path = json[KEY_PATH].GetString();
    }
    
    if ( json.HasMember(KEY_COMPRESSED) && json[KEY_COMPRESSED].IsBool() )
    {
        asset.compressed = json[KEY_COMPRESSED].GetBool();
    }
    else asset.compressed = false;
    
    if ( json.HasMember(KEY_DOWNLOAD_SIZE) && json[KEY_DOWNLOAD_SIZE].IsInt64() )
    {
        asset.downloadSize = json[KEY_DOWNLOAD_SIZE].GetInt64();
    }
    else asset.downloadSize = 0;
    
    if ( json.HasMember(KEY_DOWNLOAD_STATE) && json[KEY_DOWNLOAD_STATE].IsInt() )
    {
        asset.downloadState = (json[KEY_DOWNLOAD_STATE].GetInt());
    }
    else asset.downloadState = DownloadState::UNMARKED;

	if (json.HasMember(KEY_RESOURCE_FILE_SIZE) && json[KEY_RESOURCE_FILE_SIZE].IsInt64())
	{
		asset.fileSize = json[KEY_RESOURCE_FILE_SIZE].GetInt64();
	}
	else asset.fileSize = 0;
    
    return asset;
}

void Manifest::loadManifest(const rapidjson::Document &json)
{    
	// Retrieve remote manifest url
	if (json.HasMember(KEY_MANIFEST_URL) && json[KEY_MANIFEST_URL].IsString())
	{
		m_remoteManifestUrl = json[KEY_MANIFEST_URL].GetString();
	}

	// Retrieve local version
	if (json.HasMember(KEY_VERSION) && json[KEY_VERSION].IsString())
	{
		m_version = json[KEY_VERSION].GetString();
	}
    
    // Retrieve package url
    if ( json.HasMember(KEY_PACKAGE_URL) && json[KEY_PACKAGE_URL].IsString() )
    {
        m_packageUrl = json[KEY_PACKAGE_URL].GetString();
        // Append automatically "/"
        if (m_packageUrl.size() > 0 && m_packageUrl[m_packageUrl.size() - 1] != '/')
        {
            m_packageUrl.append("/");
        }
    }
    
    // Retrieve all assets
    if ( json.HasMember(KEY_ASSETS) )
    {
        const rapidjson::Value& assets = json[KEY_ASSETS];
        if (assets.IsObject())
        {
            for (rapidjson::Value::ConstMemberIterator itr = assets.MemberBegin(); itr != assets.MemberEnd(); ++itr)
            {
                std::string key = itr->name.GetString();
                Asset asset = parseAsset(key, itr->value);
                m_assets.emplace(key, asset);
            }
        }
    }
}

void Manifest::saveToFile(const std::string &filepath)
{
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    m_json.Accept(writer);

    FileUtils::getInstance()->writeStringToFile(buffer.GetString(), filepath);
}

//////////////////////////////////////////////////////////////////////////
void Manifest::updateExtData()
{
	if (!m_json.HasParseError() && m_json.IsObject())
	{
		if (!m_platform.empty() && m_json.HasMember(KEY_STRONG_UPDATE_VER))
		{
			const rapidjson::Value& strongUpdateVerValue = m_json[KEY_STRONG_UPDATE_VER];
			if (strongUpdateVerValue.IsObject())
			{
				for (rapidjson::Value::ConstMemberIterator itr = strongUpdateVerValue.MemberBegin(); itr != strongUpdateVerValue.MemberEnd(); ++itr)
				{
					if (itr->name.IsString() && itr->name.GetString() == m_platform && itr->value.IsInt())
					{
						m_strongUpdateVer = itr->value.GetInt();
					}
				}
			}
		}

		if (!m_platform.empty() && m_json.HasMember(KEY_STRONG_UPDATE_URL))
		{
			const rapidjson::Value& strongUpdateVerValue = m_json[KEY_STRONG_UPDATE_URL];
			if (strongUpdateVerValue.IsObject())
			{
				for (rapidjson::Value::ConstMemberIterator itr = strongUpdateVerValue.MemberBegin(); itr != strongUpdateVerValue.MemberEnd(); ++itr)
				{
					if (itr->name.IsString() && itr->name.GetString() == m_platform && itr->value.IsString())
					{
						m_strongUpdateURL = itr->value.GetString();
					}
				}
			}
		}

		if (!m_platform.empty() && m_json.HasMember(KEY_STRONG_UPDATE_DES))
		{
			const rapidjson::Value& strongUpdateVerValue = m_json[KEY_STRONG_UPDATE_DES];
			if (strongUpdateVerValue.IsObject())
			{
				for (rapidjson::Value::ConstMemberIterator itr = strongUpdateVerValue.MemberBegin(); itr != strongUpdateVerValue.MemberEnd(); ++itr)
				{
					if (itr->name.IsString() && itr->name.GetString() == m_platform && itr->value.IsString())
					{
						m_strongUpdateDescription = itr->value.GetString();
					}
				}
			}
		}

		if (m_json.HasMember(KEY_UPDATE_DESCRIPTION) && m_json[KEY_UPDATE_DESCRIPTION].IsString())
		{
			m_updateDescription = m_json[KEY_UPDATE_DESCRIPTION].GetString();
		}

		if (m_json.HasMember(KEY_RESTART_LEVEL) && m_json[KEY_RESTART_LEVEL].IsInt())
		{
			m_restartLevel = m_json[KEY_RESTART_LEVEL].GetInt();
		}

		if (m_json.HasMember(KEY_LOOSE_FILE_MODE) && m_json[KEY_LOOSE_FILE_MODE].IsBool())
		{
			m_looseFileMode = m_json[KEY_LOOSE_FILE_MODE].GetBool();
		}
	}
}

int Manifest::getStrongUpdateVersion() const
{
	return m_strongUpdateVer;
}

const std::string& Manifest::getStrongUpdateURL() const
{
	return m_strongUpdateURL;
}

bool Manifest::isNeedStrongUpdate(const Manifest* m) const
{
	return getStrongUpdateVersion() < m->getStrongUpdateVersion();
}

// 获取强更新描述
const std::string& Manifest::getStrongUpdateDescription() const
{
	return m_strongUpdateDescription;
}

const std::string& Manifest::getUpdateDescription() const
{
	return m_updateDescription;
}

int Manifest::getRestartLevel() const
{
	return m_restartLevel;
}

bool Manifest::isLooseFileMode() const
{
	return m_looseFileMode;
}

NS_AS_END