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

		// ���ڼ�����
		CHECK_UPDATE,

		// �ȴ�����
		WAIT_FOR_UPDATE,

		// ���ڸ���
        UPDATING,
		
		// �Ѿ������°汾
        UP_TO_DATE,
    };
    
    const static std::string MANIFEST_ID;
    

	/** @brief
	 @param manifestUrl   �嵥�ļ���ַ
	 @param storagePath   �����嵥�ļ�
	 @param platformName  ��ǰƽ̨����
	 */
	AssetsManager(const std::string& manifestUrl, const std::string& storagePath, const std::string& platformName);

	virtual ~AssetsManager();

    /** @brief  ���汾��׼������,�˺�����������ϸ�嵥�ļ����ҶԱ���Ӧ����
	׼����Ϻ�ᷢ�� UPDATE_FILE_SIZE �¼�,֪ͨ�ͻ�����Ҫ���µ��ļ���С,�û����� startUpdate �����ſ�ʼ�������ļ�����
     */
    bool checkUpdate(const LuaFunction& handle);

	/** @brief  ��ʼ����,�����ȵ��� checkUpdate ���������Ը��²ŵ��ñ�����
	 */
	bool startUpdate(const LuaFunction& handle);

	/** @brief  �����޸�,�����Ӧ���ļ�/Ŀ¼
	 */
	void repair();

	/** @brief ��ȡ��Ҫ���µ��ܴ�С
	*/
	double getTotalSize();
	
	/** @brief ��ȡ�Ѿ����صĴ�С
	*/
	double getDownloadSize();

	/** @brief ��ȡ���½���
	*/
	float getUpdatePercent();


    /** @brief ��ȡ�洢·��
     */
    const std::string& getStoragePath() const;
    
    /** @brief ��ȡ�����嵥�ļ�
     */
    const Manifest* getLocalManifest() const;
    
    /** @brief ��ȡԶ���嵥�ļ�
     */
    const Manifest* getRemoteManifest() const;
    
    /** @brief ��ȡ���ͬʱ�����������
     */
    int getMaxConcurrentTask() const {return m_maxConcurrentTask;};
    
    /** @brief �������ͬʱ�����������
     */
    void setMaxConcurrentTask(const int max) {m_maxConcurrentTask = max;};
	
	/** @brief �Զ�����ԴУ�麯��
	 */
	void setVerifyLuaCallback(const LuaFunction& handle);

	/** @brief �Զ�����ԴУ�麯��
	 */
    void setVerifyCallback(const std::function<bool(const std::string& path, Manifest::Asset asset)>& callback) {m_verifyCallback = callback;};
    
protected:
    
    bool initLocalManifest();
        
    void setStoragePath(const std::string& storagePath);
        
	// �����嵥�ļ�
    void downloadManifest();
	// �����嵥�ļ�
    void parseManifest();

    void updateSucceed();

	// zip��ѹ
    void decompressDownloadedZip(const std::string &customId, const std::string &storagePath);
        
    // �������
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
    
    // ��ǰ״̬
    State m_updateState;
    
    
    // ���´洢Ŀ¼
    std::string m_storagePath;
    // ������ʱĿ¼
    std::string m_tempStoragePath;

    // �����嵥�ļ�����·��
    std::string m_cacheManifestPath;
	// �����嵥�ļ�����·��
	std::string m_downloadManifestPath;
	// ��ʱ�嵥�ļ�����·��
    std::string m_tempManifestPath;
    
	// �����嵥�ļ�·��
    std::string m_manifestUrl;
	// ƽ̨����
	std::string m_platformName;
    
	// �����嵥
	Manifest *m_localManifest;
	// ��ʱ�嵥
	Manifest *m_tempManifest;
	// Զ���嵥
	Manifest *m_remoteManifest;

        
    // ������Ҫ���ص���Դ
    DownloadUnits m_downloadUnits;
    // ����ʧ�ܵ���Դ
    DownloadUnits m_failedUnits;

	// Downloader
	std::shared_ptr<cocos2d::network::Downloader> m_downloader;
    // ���ض���
    std::vector<std::string> m_downloadQueue;
    // ����������񲢷�����
    int m_maxConcurrentTask;
    // ��ǰ���ڽ��е�������������
    int m_currConcurrentTask;

	
    // �Զ�����ԴУ�麯��
    std::function<bool(const std::string& path, Manifest::Asset asset)> m_verifyCallback;
    
	
	// Lua����
	LuaFunction m_verifyLuaHandle;

	LuaFunction m_checkCallLuaHandle;
	LuaFunction m_updateCallLuaHandle;


	///////////////////////////////////////////////���㵱ǰ���ؽ���///////////////////////////////////////////////
	// ����������ݽṹ��
	struct TaskPercentData
	{
		Manifest::DownloadState state;
		int64_t totalSize;
		int64_t curSize;
	};
	// �ļ����¹���ӳ��
	std::unordered_map<std::string, TaskPercentData> m_percentFileMap;

	// �ܹ���Ҫ���µ��ļ���С
	int64_t m_totalSize;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

NS_AS_END