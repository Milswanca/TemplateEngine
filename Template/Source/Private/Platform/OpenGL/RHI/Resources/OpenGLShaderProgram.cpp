#include "Platform/OpenGL/RHI/Resources/OpenGLShaderProgram.h"
#include "Platform/OpenGL/RHI/Resources/OpenGLShader.h"

OpenGLShaderProgram::OpenGLShaderProgram()
{
	m_ProgramID = glCreateProgram();
}

OpenGLShaderProgram::~OpenGLShaderProgram()
{
	DetachShaders();
	glDeleteProgram(m_ProgramID);
}

void OpenGLShaderProgram::SetVertexShader(OpenGLVertexShader* InVertexShader)
{
	m_VertexShader = InVertexShader;
}

void OpenGLShaderProgram::SetPixelShader(OpenGLPixelShader* InPixelShader)
{
	m_PixelShader = InPixelShader;
}

OpenGLVertexShader* OpenGLShaderProgram::GetVertexShader() const
{
	return m_VertexShader;
}

OpenGLPixelShader* OpenGLShaderProgram::GetPixelShader() const
{
	return m_PixelShader;
}

void OpenGLShaderProgram::Use()
{
	glUseProgram(m_ProgramID);
}

void OpenGLShaderProgram::LinkProgram()
{
	DetachShaders();

	if (m_VertexShader)
	{
		glAttachShader(m_ProgramID, m_VertexShader->GetShaderID());
	}

	if (m_PixelShader)
	{
		glAttachShader(m_ProgramID, m_PixelShader->GetShaderID());
	}

	glLinkProgram(m_ProgramID);

	int Success;
	char InfoLog[512];
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Success);
	if(!Success) {
		glGetProgramInfoLog(m_ProgramID, 512, NULL, InfoLog);
		std::cout << "ERROR::SHADERPROGRAM::COMPILATION_FAILED\n" << InfoLog << std::endl;
	}
}

void OpenGLShaderProgram::DetachShaders()
{
	GLint Count;
	GLuint Shaders[5];
	glGetAttachedShaders(m_ProgramID, 5, &Count, Shaders);

	for (int i = 0; i < Count; ++i)
	{
		glDetachShader(m_ProgramID, Shaders[i]);
	}
}