#include "Utils/StringUtils.h"

#include <algorithm>
#include <sstream>
#include <vector>

std::vector<std::string> StringUtils::Split(const std::string& InString, const char InDelimeter)
{
    std::vector<std::string> OutStrings;

    std::istringstream F(InString);
    std::string S;

    while (getline(F, S, InDelimeter))
    {
        OutStrings.push_back(S);
    }

    return OutStrings;
}

std::string StringUtils::Join(const std::vector<std::string>& InStrArray, const char InDelimeter)
{
    std::string Ret;

    for (size_t i = 0; i < InStrArray.size(); ++i)
    {
        Ret += InStrArray[i] + InDelimeter;
    }

    Ret.pop_back();
    return Ret;
}

std::string StringUtils::Replace(const std::string& InStr, char InFrom, char InTo)
{
    std::string S = InStr;
    std::replace(S.begin(), S.end(), InFrom, InTo);
    return S;
}
