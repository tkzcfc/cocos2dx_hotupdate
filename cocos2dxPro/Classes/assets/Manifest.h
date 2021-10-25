#pragma once

#include "AssetsHeader.h"

NS_AS_BEGIN

struct DownloadUnit
{
    std::string srcUrl;
    std::string storagePath;
    std::string customId;
	// 已下载的大小
	int64_t       downloadSize;

	// 清单文件中fileSize字段
	int64_t fileSize;
};

struct ManifestAsset {
    std::string md5;
    std::string path;
    bool compressed;
	int64_t downloadSize;
    int downloadState;

	// 清单文件中fileSize字段
	int64_t fileSize;
};

typedef std::unordered_map<std::string, DownloadUnit> DownloadUnits;

class Manifest
{
public:
    
    friend class AssetsManager;
    
    //! The type of difference
    enum DiffType {
        ADDED,
        DELETED,
        MODIFIED
    };
    
    enum DownloadState {
        UNSTARTED,
        DOWNLOADING,
        SUCCESSED,
        UNMARKED
    };
    
    //! Asset object
    typedef ManifestAsset Asset;
    
    //! Object indicate the difference between two Assets
    struct AssetDiff {
        Asset asset;
        DiffType type;
    };
    
    /** @brief Check whether the manifest have been fully loaded
     */
    bool isLoaded() const;
	
	// 获取强更新地址
	const std::string& getStrongUpdateURL() const;
    
	// 获取更新描述
	const std::string& getUpdateDescription() const;

	// 获取强更新描述
	const std::string& getStrongUpdateDescription() const;

	// 重新启动等级
	// 0 不需要重启  1 程序自动重启 2 用户重启
	int getRestartLevel() const;

	// 是否是散文件更新
	bool isLooseFileMode() const;

    /** @brief Gets remote package url.
     */
    const std::string& getPackageUrl() const;
    
    /** @brief Gets remote manifest file url.
     */
    const std::string& getManifestFileUrl() const;
    
    /** @brief Gets manifest version.
     */
    const std::string& getVersion() const;
        
protected:
    
    /** @brief Constructor for Manifest class
     * @param manifestUrl Url of the local manifest
     */
    Manifest(const std::string& manifestUrl, const std::string& platform);
    
    /** @brief Load the json file into local json object
     * @param url Url of the json file
     */
    bool loadJson(const std::string& url);
    
    /** @brief Parse the manifest file information into this manifest
     * @param manifestUrl Url of the local manifest
     */
    void parse(const std::string& manifestUrl);
    
    /** @brief Check whether the version of this manifest equals to another.
     * @param b   The other manifest
     * @return Equal or not
     */
    bool versionEquals(const Manifest *b) const;
    
    /** @brief Check whether the version of this manifest is greater than another.
     * @param b         The other manifest
     * @param [handle]  Customized comparasion handle function
     * @return Greater or not
     */
    bool versionGreater(const Manifest *b) const;
    
    /** @brief Generate difference between this Manifest and another.
     * @param b   The other manifest
     */
    std::unordered_map<std::string, AssetDiff> genDiff(const Manifest *b) const;
    
    /** @brief Generate resuming download assets list
     * @param units   The download units reference to be modified by the generation result
     */
    void genResumeAssetsList(DownloadUnits *units) const;
            
    void loadManifest(const rapidjson::Document &json);
    
    void saveToFile(const std::string &filepath);
    
    Asset parseAsset(const std::string &path, const rapidjson::Value &json);
    
    void clear();
    
    /** 
     * @brief Gets assets.
     * @lua NA
     */
    const std::unordered_map<std::string, Asset>& getAssets() const;
    
    /** @brief Set the download state for an asset
     * @param key   Key of the asset to set
     * @param state The current download state of the asset
     */
    void setAssetDownloadState(const std::string &key, const DownloadState &state);

	void setAssetDownloadSize(const std::string &key, int64_t downloadSize);

    
    void setManifestRoot(const std::string &root) {m_manifestRoot = root;};

	void updateExtData();

	int getStrongUpdateVersion() const;

	bool isNeedStrongUpdate(const Manifest* m) const;

private:
        
    //! Indicate whether the manifest have been fully loaded
    bool m_loaded;
	        
    //! The local manifest root
    std::string m_manifestRoot;
    
    //! The remote package url
    std::string m_packageUrl;
    
    //! The remote path of manifest file
    std::string m_remoteManifestUrl;
        
    //! The version of local manifest
    std::string m_version;
    
    //! Full assets list
    std::unordered_map<std::string, Asset> m_assets;
        
    rapidjson::Document m_json;

	std::string m_updateDescription;

	int m_restartLevel;

	std::string m_platform;

	int m_strongUpdateVer;

	std::string m_strongUpdateURL;

	std::string m_strongUpdateDescription;

	bool m_looseFileMode;
};

NS_AS_END
