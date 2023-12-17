#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShader.h"
#include <iostream>

OpenGLShader::OpenGLShader(GLenum InShaderType)
{
	m_ShaderType = InShaderType;
	m_ShaderID = glCreateShader(InShaderType);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteShader(m_ShaderID);
}

void OpenGLShader::SetShaderSource(std::string_view InSource)
{
	glShaderSource(m_ShaderID, 1, (const GLchar* const*)InSource.data(), 0);
}

void OpenGLShader::Compile()
{
	glCompileShader(m_ShaderID);

	int Success;
	char InfoLog[512];

	// print compile errors if any
	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(m_ShaderID, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << InfoLog << std::endl;
	};
}