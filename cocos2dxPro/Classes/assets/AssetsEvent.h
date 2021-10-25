#pragma once

#include "AssetsHeader.h"

NS_AS_BEGIN

enum AssetsEventCode
{
	////////////////////////////// 检查更新阶段返回的错误码 //////////////////////////////

	// 错误:找不到本地的清单文件
	ERROR_NO_LOCAL_MANIFEST,
	// 错误:远程清单文件下载失败
	ERROR_DOWNLOAD_MANIFEST,
	// 错误:清单文件解析失败
	ERROR_PARSE_MANIFEST,

	// 通知:需要强更新
	NEED_STRONG_UPDATE,
	// 通知:发现新版本
	NEW_VERSION_FOUND,
	// 通知:已经是最新版本了
	ALREADY_UP_TO_DATE,


	////////////////////////////// 正在更新阶段返回的错误码 //////////////////////////////
	// 错误:资源解压失败
	ERROR_DECOMPRESS,
	// 错误:有资源下载失败
	ERROR_DOWNLOAD,
	// 错误:资源校验失败
	ERROR_VERIF,
	// 更新成功
	SUCCESS,
};

NS_AS_END