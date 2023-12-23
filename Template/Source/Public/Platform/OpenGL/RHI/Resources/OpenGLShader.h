#pragma once
#include "Rendering/RHI/Resources/RHIShader.h"
#include <string_view>
#include <glad/glad.h>
#include <unordered_map>
#include <iostream>

class OpenGLShader : public virtual RHIShader
{
public:
	OpenGLShader(EShaderTypes InShaderType);
	~OpenGLShader();

	void SetShaderSource(std::string_view InSource);
	void Compile();

	GLuint GetShaderID() const { return m_GLShaderID; }

protected:
	static std::unordered_map<EShaderTypes, GLenum> s_ShaderTypesToGLTypes;

private:
	GLuint m_GLShaderID = -1;
	GLenum m_GLShaderType = GL_NONE;
};

class OpenGLVertexShader : public RHIVertexShader, public OpenGLShader
{
public:
	OpenGLVertexShader() : OpenGLShader(EShaderTypes::Vertex), RHIVertexShader(), RHIShader(EShaderTypes::Vertex) {}
};

class OpenGLPixelShader : public RHIPixelShader, public OpenGLShader
{
public:
	OpenGLPixelShader() : OpenGLShader(EShaderTypes::Pixel), RHIPixelShader(), RHIShader(EShaderTypes::Pixel) {}
};