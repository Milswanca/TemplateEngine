#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShader.h"
#include <iostream>

std::unordered_map<EShaderTypes, GLenum> OpenGLShader::s_ShaderTypesToGLTypes = {
	{ EShaderTypes::Vertex, GL_VERTEX_SHADER },
	{ EShaderTypes::Pixel, GL_FRAGMENT_SHADER }
};

OpenGLShader::OpenGLShader(EShaderTypes InShaderType) : RHIShader(InShaderType)
{
	m_GLShaderType = s_ShaderTypesToGLTypes[InShaderType];
	m_GLShaderID = glCreateShader(m_GLShaderType);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteShader(m_GLShaderID);
}

void OpenGLShader::SetShaderSource(std::string_view InSource)
{
	glShaderSource(m_GLShaderID, 1, (const GLchar* const*)InSource.data(), 0);
}

void OpenGLShader::Compile()
{
	glCompileShader(m_GLShaderID);

	int Success;
	char InfoLog[512];

	// print compile errors if any
	glGetShaderiv(m_GLShaderID, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(m_GLShaderID, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << InfoLog << std::endl;
	};
}