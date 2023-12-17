#pragma once
#include "Rendering/RHI/Resources/RHIShader.h"
#include <string_view>
#include <glad/glad.h>

class OpenGLShader
{
public:
	OpenGLShader(GLenum InShaderType);
	~OpenGLShader();

	void SetShaderSource(std::string_view InSource);
	void Compile();

	GLuint GetShaderID() const { return m_ShaderID; }

private:
	GLuint m_ShaderID = -1;
	GLenum m_ShaderType = GL_NONE;
};

class OpenGLVertexShader : public RHIVertexShader, public OpenGLShader
{
public:
	OpenGLVertexShader() : OpenGLShader(GL_VERTEX_SHADER) {}
};

class OpenGLPixelShader : public RHIPixelShader, public OpenGLShader
{
public:
	OpenGLPixelShader() : OpenGLShader(GL_FRAGMENT_SHADER) {}
};