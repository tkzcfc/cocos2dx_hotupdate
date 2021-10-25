#include "Utils.h"
#include "tinydir/tinydir.h"
#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "external/unzip/unzip.h"
#endif

NS_AS_BEGIN


using namespace cocos2d;


#define BUFFER_SIZE    8192
#define MAX_FILENAME   512


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

static std::wstring StringUtf8ToWideChar(const std::string& strUtf8)
{
	std::wstring ret;
	if (!strUtf8.empty())
	{
		int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
		if (nNum)
		{
			WCHAR* wideCharString = new WCHAR[nNum + 1];
			wideCharString[0] = 0;

			nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

			ret = wideCharString;
			delete[] wideCharString;
		}
		else
		{
			CCLOG("Wrong convert to WideChar code:0x%x", GetLastError());
		}
	}
	return ret;
}

static std::string StringWideCharToUtf8(const std::wstring& strWideChar)
{
	std::string ret;
	if (!strWideChar.empty())
	{
		int nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
		if (nNum)
		{
			char* utf8String = new char[nNum + 1];
			utf8String[0] = 0;

			nNum = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, nNum + 1, nullptr, FALSE);

			ret = utf8String;
			delete[] utf8String;
		}
		else
		{
			CCLOG("Wrong convert to Utf8 code:0x%x", GetLastError());
		}
	}

	return ret;
}

void Utils::listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files)
{
	FileUtils* fileUtils = FileUtils::getInstance();
	std::string fullpath = fileUtils->fullPathForFilename(dirPath);
	if (fileUtils->isDirectoryExist(fullpath))
	{
		tinydir_dir dir;
		std::wstring fullpathstr = StringUtf8ToWideChar(fullpath);

		if (tinydir_open(&dir, &fullpathstr[0]) != -1)
		{
			while (dir.has_next)
			{
				tinydir_file file;
				if (tinydir_readfile(&dir, &file) == -1)
				{
					// Error getting file
					break;
				}
				std::string fileName = StringWideCharToUtf8(file.name);

				if (fileName != "." && fileName != "..")
				{
					std::string filepath = StringWideCharToUtf8(file.path);
					if (file.is_dir)
					{
						filepath.append("/");
						files->push_back(filepath);
						listFilesRecursively(filepath, files);
					}
					else
					{
						files->push_back(filepath);
					}
				}

				if (tinydir_next(&dir) == -1)
				{
					// Error getting next file
					break;
				}
			}
		}
		tinydir_close(&dir);
	}
}
#else
void Utils::listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files)
{
	FileUtils* fileUtils = FileUtils::getInstance();

	std::string fullpath = fileUtils->fullPathForFilename(dirPath);
	if (fileUtils->isDirectoryExist(fullpath))
	{
		tinydir_dir dir;
		std::string fullpathstr = fullpath;

		if (tinydir_open(&dir, &fullpathstr[0]) != -1)
		{
			while (dir.has_next)
			{
				tinydir_file file;
				if (tinydir_readfile(&dir, &file) == -1)
				{
					// Error getting file
					break;
				}
				std::string fileName = file.name;

				if (fileName != "." && fileName != "..")
				{
					std::string filepath = file.path;
					if (file.is_dir)
					{
						filepath.append("/");
						files->push_back(filepath);
						listFilesRecursively(filepath, files);
					}
					else
					{
						files->push_back(filepath);
					}
				}

				if (tinydir_next(&dir) == -1)
				{
					// Error getting next file
					break;
				}
			}
		}
		tinydir_close(&dir);
	}
}
#endif


bool Utils::decompressZip(const std::string &zip, std::string& errorStr)
{
	// Find root path for zip file
	size_t pos = zip.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		errorStr = cocos2d::StringUtils::format("no root path specified for zip file %s\n", zip.c_str());
		return false;
	}
	const std::string rootPath = zip.substr(0, pos + 1);

	// Open the zip file
	unzFile zipfile = cocos2d::unzOpen(cocos2d::FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
	if (!zipfile)
	{
		errorStr = cocos2d::StringUtils::format("can not open downloaded zip file %s\n", zip.c_str());
		return false;
	}

	// Get info about the zip file
	cocos2d::unz_global_info global_info;
	if (cocos2d::unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		errorStr = cocos2d::StringUtils::format("can not read file global info of %s\n", zip.c_str());
		cocos2d::unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		cocos2d::unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (cocos2d::unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			errorStr = cocos2d::StringUtils::format("can not read compressed file info\n");
			cocos2d::unzClose(zipfile);
			return false;
		}
		const std::string fullPath = rootPath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			//There are not directory entry in some case.
			//So we need to create directory when decompressing file entry
			if (!cocos2d::FileUtils::getInstance()->createDirectory(basename(fullPath)))
			{
				// Failed to create directory
				errorStr = cocos2d::StringUtils::format("can not create directory %s\n", fullPath.c_str());
				cocos2d::unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Create all directories in advance to avoid issue
			std::string dir = basename(fullPath);
			if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(dir)) {
				if (!cocos2d::FileUtils::getInstance()->createDirectory(dir)) {
					// Failed to create directory
					errorStr = cocos2d::StringUtils::format("can not create directory %s\n", fullPath.c_str());
					cocos2d::unzClose(zipfile);
					return false;
				}
			}
			// Entry is a file, so extract it.
			// Open current file.
			if (cocos2d::unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				errorStr = cocos2d::StringUtils::format("can not extract file %s\n", fileName);
				cocos2d::unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(cocos2d::FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
			if (!out)
			{
				errorStr = cocos2d::StringUtils::format("can not create decompress destination file %s (errno: %d)\n", fullPath.c_str(), errno);
				cocos2d::unzCloseCurrentFile(zipfile);
				cocos2d::unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = cocos2d::unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					errorStr = cocos2d::StringUtils::format("can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					cocos2d::unzCloseCurrentFile(zipfile);
					cocos2d::unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		cocos2d::unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (cocos2d::unzGoToNextFile(zipfile) != UNZ_OK)
			{
				errorStr = cocos2d::StringUtils::format("can not read next file for decompressing\n");
				cocos2d::unzClose(zipfile);
				return false;
			}
		}
	}

	cocos2d::unzClose(zipfile);
	return true;
}


std::string Utils::basename(const std::string& path)
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found);
	}
	else
	{
		return path;
	}
}


void Utils::adjustPath(std::string &path)
{
	if (path.size() > 0 && path[path.size() - 1] != '/')
	{
		path.append("/");
	}
}

bool Utils::removeFile(const std::string& filepath)
{
	auto fileUtils = cocos2d::FileUtils::getInstance();
	if (fileUtils->isFileExist(filepath))
	{
		return fileUtils->removeFile(filepath);
	}
	return true;
}

void Utils::replace(std::string& str, const std::string& old_value, const std::string& new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != std::string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else { break; }
	}
}

NS_AS_END
