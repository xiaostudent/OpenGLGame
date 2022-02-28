#pragma once

#ifndef BASE_FILEUTIL
#define BASE_FILEUTIL
#include <xstring>
#include <Windows.h>

class FileUtil
{
public:
	static std::string getFileString(std::string path);
    static std::string getRootPath();
};

#endif // !1

