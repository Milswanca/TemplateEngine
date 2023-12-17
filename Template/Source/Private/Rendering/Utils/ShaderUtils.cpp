#include "Rendering/Utils/ShaderUtils.h"

#include "Utils/FileUtils.h"
#include <fstream>
#include <iostream>

bool ShaderUtils::LoadShaderContents(const std::string& InFile, std::string& OutContents)
{
	std::ifstream Stream(InFile.c_str());

	if (!Stream.is_open())
	{
		std::cerr << "Failed to open shader file " << InFile;
		return false;
	}

	OutContents = "";
	std::string IncludeIdentifier = "#include";
	std::string LineBuffer;

	while (std::getline(Stream, LineBuffer))
	{
		if (LineBuffer.find(IncludeIdentifier) != LineBuffer.npos)
		{
			// Remove the include identifier, this will cause the path to remain
			// +1 to remove the space
			LineBuffer.erase(0, IncludeIdentifier.size() + 1);

			// The include path is relative to the current shader file path
			std::string PathOfThisFile = FileUtils::GetDirectory(InFile);
			LineBuffer.insert(0, PathOfThisFile);

			std::string IncludeContents;
			if (!LoadShaderContents(LineBuffer, IncludeContents))
				return false;

			OutContents += IncludeContents;

			// Remove the null terminator from the include
			OutContents.erase(OutContents.length() - 1);

			// Do not add this line to the shader source code, as the include
			// path would generate a compilation issue in the final source code
			continue;
		}

		OutContents += LineBuffer + '\n';
	}

	// Only add the null terminator at the end of the complete file,
	// essentially skipping recursive function calls this way
	OutContents += '\0';

	Stream.close();
	return true;
}