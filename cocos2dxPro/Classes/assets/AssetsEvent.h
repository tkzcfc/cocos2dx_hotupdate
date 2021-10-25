#pragma once

#include "AssetsHeader.h"

NS_AS_BEGIN

enum AssetsEventCode
{
	////////////////////////////// �����½׶η��صĴ����� //////////////////////////////

	// ����:�Ҳ������ص��嵥�ļ�
	ERROR_NO_LOCAL_MANIFEST,
	// ����:Զ���嵥�ļ�����ʧ��
	ERROR_DOWNLOAD_MANIFEST,
	// ����:�嵥�ļ�����ʧ��
	ERROR_PARSE_MANIFEST,

	// ֪ͨ:��Ҫǿ����
	NEED_STRONG_UPDATE,
	// ֪ͨ:�����°汾
	NEW_VERSION_FOUND,
	// ֪ͨ:�Ѿ������°汾��
	ALREADY_UP_TO_DATE,


	////////////////////////////// ���ڸ��½׶η��صĴ����� //////////////////////////////
	// ����:��Դ��ѹʧ��
	ERROR_DECOMPRESS,
	// ����:����Դ����ʧ��
	ERROR_DOWNLOAD,
	// ����:��ԴУ��ʧ��
	ERROR_VERIF,
	// ���³ɹ�
	SUCCESS,
};

NS_AS_END