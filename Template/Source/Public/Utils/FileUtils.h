#pragma once
#include <string>
#include "Core/Object.h"

class FileUtils : public Object
{
public:
    static bool DoesFileExist(const std::string& InFile);
    static bool LoadFileToString(const std::string& InFile, std::string& OutDest);
    static std::string GetPathExtension(const std::string& InFile, bool InIncludeDot = false);
    static std::string GetDirectory(const std::string& InPath);

    static bool FindRelativePath(const std::string& InBaseDir, const std::string& InAbsolutePath, std::string& OutPath);

    static std::string GetContentDirectory();
};
