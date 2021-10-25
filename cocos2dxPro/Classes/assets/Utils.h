#pragma once

#include "AssetsHeader.h"


NS_AS_BEGIN

class Utils
{
public:

	static void listFilesRecursively(const std::string& dirPath, std::vector<std::string> *files);

	template<typename T>
	static std::string toString(T arg)
	{
		std::stringstream ss;
		ss << arg;
		return ss.str();
	}

	//static void fetch(const std::string url, const std::string&identifier );

	static bool decompressZip(const std::string &zip, std::string& errorStr);

	static std::string basename(const std::string& path);

	static void adjustPath(std::string &path);

	static bool removeFile(const std::string& filepath);

	static void replace(std::string& str, const std::string& old_value, const std::string& new_value);
};

NS_AS_END
