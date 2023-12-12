#pragma once
#include <string>

// Helper class to convert file paths in a simple way to registered locations.
// CONVERSIONS:
// "Game/" - to the game content directory.
// "Engine/" - to the engine content directory.
struct FilePath
{
	FilePath() = default;
	~FilePath() = default;

	FilePath(const std::string& InPath)
	{
		m_Path = InPath;

		if (m_Path.rfind("Game/", 0) == 0)
		{

		}
	}

	operator std::string() const
	{
		return m_Path;
	}

private:
	std::string m_Path;

	// Fully converted path.
	// See: Class Description.
	std::string m_TruePath;
};

