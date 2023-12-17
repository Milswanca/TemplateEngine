#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShaderProgram.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShader.h"

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

void OpenGLShaderProgram::LinkProgram()
{
	DetachShaders();

	if (m_VertexShader)
	{
		glAttachShader(GL_VERTEX_SHADER, m_VertexShader->GetShaderID());
	}

	if (m_PixelShader)
	{
		glAttachShader(GL_FRAGMENT_SHADER, m_PixelShader->GetShaderID());
	}

	glLinkProgram(m_ProgramID);
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