#pragma once
#include <string>

class ShaderUtils
{
public:
	static bool LoadShaderContents(const std::string& InFile, std::string& OutContents);
};