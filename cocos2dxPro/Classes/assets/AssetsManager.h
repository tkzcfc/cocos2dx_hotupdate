#pragma once

#include "AssetsEvent.h"
#include "Manifest.h"
#include "LuaFunction.h"
#include "Utils.h"
#include "network/CCDownloader.h"

NS_AS_BEGIN

class AssetsManager
{
public:
    
    // Update states
    enum State
    {
        UNCHECKED,

		// 正在检查更新
		CHECK_UPDATE,

		// 等待更新
		WAIT_FOR_UPDATE,

		// 正在更新
        UPDATING,
		
		// 已经是最新版本
        UP_TO_DATE,
    };
    
    const static std::string MANIFEST_ID;
    

	/** @brief
	 @param manifestUrl   清单文件地址
	 @param storagePath   本地清单文件
	 @param platformName  当前平台名称
	 */
	AssetsManager(const std::string& manifestUrl, const std::string& storagePath, const std::string& platformName);

	virtual ~AssetsManager();

    /** @brief  检查版本并准备升级,此函数仅下载详细清单文件并且对比相应差异
	准备完毕后会发送 UPDATE_FILE_SIZE 事件,通知客户端需要更新的文件大小,用户调用 startUpdate 函数才开始真正的文件下载
     */
    bool checkUpdate(const LuaFunction& handle);

	/** @brief  开始更新,必须先调用 checkUpdate 函数检查可以更新才调用本函数
	 */
	bool startUpdate(const LuaFunction& handle);

	/** @brief  更新修复,清空相应的文件/目录
	 */
	void repair();

	/** @brief 获取需要更新的总大小
	*/
	double getTotalSize();
	
	/** @brief 获取已经下载的大小
	*/
	double getDownloadSize();

	/** @brief 获取更新进度
	*/
	float getUpdatePercent();


    /** @brief 获取存储路径
     */
    const std::string& getStoragePath() const;
    
    /** @brief 获取本地清单文件
     */
    const Manifest* getLocalManifest() const;
    
    /** @brief 获取远程清单文件
     */
    const Manifest* getRemoteManifest() const;
    
    /** @brief 获取最大同时进行任务个数
     */
    int getMaxConcurrentTask() const {return m_maxConcurrentTask;};
    
    /** @brief 设置最大同时进行任务个数
     */
    void setMaxConcurrentTask(const int max) {m_maxConcurrentTask = max;};
	
	/** @brief 自定义资源校验函数
	 */
	void setVerifyLuaCallback(const LuaFunction& handle);

	/** @brief 自定义资源校验函数
	 */
    void setVerifyCallback(const std::function<bool(const std::string& path, Manifest::Asset asset)>& callback) {m_verifyCallback = callback;};
    
protected:
    
    bool initLocalManifest();
        
    void setStoragePath(const std::string& storagePath);
        
	// 下载清单文件
    void downloadManifest();
	// 解析清单文件
    void parseManifest();

    void updateSucceed();

	// zip解压
    void decompressDownloadedZip(const std::string &customId, const std::string &storagePath);
        
    // 下载相关
	void batchDownload();

    void queueDowload();

	void onDownloadUnitsFinished();
    
    void fileError(const std::string& identifier);
    
    void fileSuccess(const std::string &customId, const std::string &storagePath);
    
    virtual void onError(const cocos2d::network::DownloadTask& task,
                         int errorCode,
                         int errorCodeInternal,
                         const std::string& errorStr);
    
    virtual void onProgress(int64_t total, int64_t downloaded, const std::string &url, const std::string &customId);
    
    virtual void onSuccess(const std::string &srcUrl, const std::string &storagePath, const std::string &customId);
    

	void savePercentFile();

	bool calculateUpdateFileSize();
	

private:

	void dispatchCheckUpdateEvent(bool success, AssetsEventCode code);

	void dispatchUpdateEvent(bool finish, AssetsEventCode code, const std::string& msg);

private:
    
    // Reference to the global file utils
    cocos2d::FileUtils *m_fileUtils;
    
    // 当前状态
    State m_updateState;
    
    
    // 更新存储目录
    std::string m_storagePath;
    // 更新临时目录
    std::string m_tempStoragePath;

    // 缓存清单文件保存路径
    std::string m_cacheManifestPath;
	// 下载清单文件保存路径
	std::string m_downloadManifestPath;
	// 临时清单文件保存路径
    std::string m_tempManifestPath;
    
	// 本地清单文件路径
    std::string m_manifestUrl;
	// 平台名称
	std::string m_platformName;
    
	// 本地清单
	Manifest *m_localManifest;
	// 临时清单
	Manifest *m_tempManifest;
	// 远程清单
	Manifest *m_remoteManifest;

        
    // 所有需要下载的资源
    DownloadUnits m_downloadUnits;
    // 下载失败的资源
    DownloadUnits m_failedUnits;

	// Downloader
	std::shared_ptr<cocos2d::network::Downloader> m_downloader;
    // 下载队列
    std::vector<std::string> m_downloadQueue;
    // 最大下载任务并发数量
    int m_maxConcurrentTask;
    // 当前正在进行的下载任务数量
    int m_currConcurrentTask;

	
    // 自定义资源校验函数
    std::function<bool(const std::string& path, Manifest::Asset asset)> m_verifyCallback;
    
	
	// Lua函数
	LuaFunction m_verifyLuaHandle;

	LuaFunction m_checkCallLuaHandle;
	LuaFunction m_updateCallLuaHandle;


	///////////////////////////////////////////////计算当前下载进度///////////////////////////////////////////////
	// 任务进度数据结构体
	struct TaskPercentData
	{
		Manifest::DownloadState state;
		int64_t totalSize;
		int64_t curSize;
	};
	// 文件更新管理映射
	std::unordered_map<std::string, TaskPercentData> m_percentFileMap;

	// 总共需要更新的文件大小
	int64_t m_totalSize;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

NS_AS_END