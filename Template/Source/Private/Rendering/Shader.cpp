#include "Rendering/Shader.h"
#include "Core/Engine.h"
#include "Utils/FileUtils.h"
#include <fstream>
#include <iostream>

Shader* Shader::Create(const FCreateShaderParams& Params)
{
	Shader* NewShader = Engine::Get()->NewObject<Shader>();

	if (Params.m_VertexShader.size() > 0) NewShader->AddShader(EShaderTypes::Vertex, Params.m_VertexShader);
	if (Params.m_FragmentShader.size() > 0) NewShader->AddShader(EShaderTypes::Fragment, Params.m_FragmentShader);
	if (Params.m_TessControlShader.size() > 0) NewShader->AddShader(EShaderTypes::TessControl, Params.m_TessControlShader);
	if (Params.m_TessEvalShader.size() > 0) NewShader->AddShader(EShaderTypes::TessEval, Params.m_TessEvalShader);

	NewShader->Compile();
	return NewShader;
}

void Shader::Begin()
{
	m_ShaderFlags = 0;
	m_ProgramID = glCreateProgram();
	m_ShaderIDs[static_cast<int>(EShaderTypes::Vertex)] = glCreateShader(GL_VERTEX_SHADER);
	m_ShaderIDs[static_cast<int>(EShaderTypes::Fragment)] = glCreateShader(GL_FRAGMENT_SHADER);
	m_ShaderIDs[static_cast<int>(EShaderTypes::TessControl)] = glCreateShader(GL_TESS_CONTROL_SHADER);
	m_ShaderIDs[static_cast<int>(EShaderTypes::TessEval)] = glCreateShader(GL_TESS_EVALUATION_SHADER);
}

void Shader::End()
{
	glDeleteProgram(m_ProgramID);
	glDeleteShader(m_ShaderIDs[static_cast<int>(EShaderTypes::Vertex)]);
	glDeleteShader(m_ShaderIDs[static_cast<int>(EShaderTypes::Fragment)]);
	glDeleteShader(m_ShaderIDs[static_cast<int>(EShaderTypes::TessControl)]);
	glDeleteShader(m_ShaderIDs[static_cast<int>(EShaderTypes::TessEval)]);
}

void Shader::AddShader(EShaderTypes Type, const std::string& Source)
{
	std::string File;

	if (LoadShaderProgram(Source, File))
	{
		m_ShaderSources[static_cast<unsigned int>(Type)] = Source;
		const char* CharPtr = File.c_str();
		m_ShaderFlags |= (1 << static_cast<int>(Type));
		glShaderSource(m_ShaderIDs[static_cast<int>(Type)], 1, &CharPtr, 0);
	}
	else
	{
		// Throw invalid file error
		std::cerr << "Failed to load shader program " << Source;
	}
}

void Shader::RemoveShader(EShaderTypes InType)
{
	glShaderSource(m_ShaderIDs[static_cast<int>(InType)], 1, nullptr, 0);
	m_ShaderFlags &= ~(1 << static_cast<int>(InType));
}

bool Shader::LoadShaderProgram(const std::string& InFile, std::string& InContents) const
{
	std::ifstream Stream(InFile.c_str());

	if (!Stream.is_open())
	{
		std::cerr << "Failed to open shader file " << InFile;
		return false;
	}

	InContents = "";
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
			if (!LoadShaderProgram(LineBuffer, IncludeContents))
				return false;

			InContents += IncludeContents;

			// Remove the null terminator from the include
			InContents.erase(InContents.length() - 1);

			// Do not add this line to the shader source code, as the include
			// path would generate a compilation issue in the final source code
			continue;
		}

		InContents += LineBuffer + '\n';
	}

	// Only add the null terminator at the end of the complete file,
	// essentially skipping recursive function calls this way
	InContents += '\0';

	Stream.close();
	return true;
}

void Shader::Compile()
{
	GLint Count;
	GLuint Shaders[5];
	glGetAttachedShaders(m_ProgramID, 5, &Count, Shaders);

	for (int i = 0; i < Count; ++i)
	{
		glDetachShader(m_ProgramID, Shaders[i]);
	}

	for (unsigned int i = 0; i < static_cast<unsigned int>(EShaderTypes::COUNT); ++i)
	{
		if (HasShaderType(static_cast<EShaderTypes>(i)))
		{
			glCompileShader(m_ShaderIDs[i]);

			int Success;
			char InfoLog[512];

			// print compile errors if any
			glGetShaderiv(m_ShaderIDs[i], GL_COMPILE_STATUS, &Success);
			if (!Success)
			{
				glGetShaderInfoLog(m_ShaderIDs[i], 512, NULL, InfoLog);
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << InfoLog << std::endl;
			};

			glAttachShader(m_ProgramID, m_ShaderIDs[i]);
		}
	}

	glLinkProgram(m_ProgramID);
	CacheParameters();
}

void Shader::CacheParameters()
{
	m_Parameters.empty();

	glUseProgram(GetProgramID());

	GLint Count;
	glGetProgramiv(GetProgramID(), GL_ACTIVE_UNIFORMS, &Count);

	for (GLint i = 0; i < Count; i++)
	{
		FShaderParameterCache Param;
		GLint Length;
		GLint Size;
		GLenum Type;
		GLchar Name[24];
		glGetActiveUniform(GetProgramID(), (GLuint)i, 24, &Length, &Size, &Type, Name);
		Param.m_ParameterLocation = glGetUniformLocation(GetProgramID(), Name);
		Param.m_ParameterName = std::string(Name);

		m_Parameters[Param.m_ParameterName] = Param;
	}
}

bool Shader::HasShaderType(EShaderTypes Type) const
{
	return (m_ShaderFlags & (1 << (static_cast<int>(Type)))) != 0;
}

unsigned int Shader::GetProgramID() const
{
	return m_ProgramID;
}

int Shader::GetParameterLocation(const std::string& Name) const
{
	auto Iter = m_Parameters.find(Name);

	if (Iter == m_Parameters.end())
	{
		return -1;
	}

	return Iter->second.m_ParameterLocation;
}