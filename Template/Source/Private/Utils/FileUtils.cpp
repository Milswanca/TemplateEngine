#include "Utils/FileUtils.h"
#include "Utils/StringUtils.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>

bool FileUtils::DoesFileExist(const std::string& InFile)
{
    struct stat Buffer;   
    return (stat (InFile.c_str(), &Buffer) == 0); 
}

bool FileUtils::LoadFileToString(const std::string& InFile, std::string& OutDest)
{
    std::ifstream F(InFile);
    if(F)
    {
        std::ostringstream SS;
        SS << F.rdbuf();
        OutDest = SS.str();
        return true;
    }
    
    return false;
}

std::string FileUtils::GetPathExtension(const std::string& InFile, bool InIncludeDot)
{
    if(InFile.find_last_of(".") != std::string::npos)
    {
        return InFile.substr(InFile.find_last_of('.') + (InIncludeDot ? 0 : 1));
    }

    return "";
}

std::string FileUtils::GetDirectory(const std::string& InPath)
{
    size_t Pos = InPath.find_last_of("\\/");
    return (std::string::npos == Pos) ? "" : InPath.substr(0, Pos + 1);
}

bool FileUtils::FindRelativePath(const std::string& InBaseDir, const std::string& InAbsolutePath, std::string& OutPath)
{
    std::string SAbsolutePath = StringUtils::Replace(InAbsolutePath, '/', '\\');
    std::string SBaseDir = StringUtils::Replace(InBaseDir, '/', '\\');
    
    if(DoesFileExist(SAbsolutePath))
    {
        OutPath = SAbsolutePath;
        return true;
    }

    std::vector<std::string> Split = StringUtils::Split(SAbsolutePath, '\\');
    for(int i = Split.size() - 1; i >= 0; --i)
    {
        std::string TestPath = SBaseDir + Split[i];

        int CurrIdx = i + 1;
        while(DoesFileExist(TestPath))
        {
            if(CurrIdx >= Split.size())
            {
                OutPath = TestPath;
                return true;
            }

            TestPath += "\\" + Split[CurrIdx];
            CurrIdx++;
        }
    }

    return false;
}

std::string FileUtils::GetContentDirectory()
{
	char Buffer[MAX_PATH];
	GetModuleFileNameA(NULL, Buffer, MAX_PATH);
	std::string::size_type pos = std::string(Buffer).find_last_of("\\/");

	return std::string(Buffer).substr(0, pos) + "/Content/";
}
