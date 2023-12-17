#pragma once
#include "Rendering/RHI/Resources/RHIShaderProgram.h"
#include <glad/glad.h>

class OpenGLVertexShader;
class OpenGLPixelShader;

class OpenGLShaderProgram : public RHIShaderProgram
{
public:
	OpenGLShaderProgram();
	~OpenGLShaderProgram();

	void SetVertexShader(OpenGLVertexShader* InVertexShader);
	void SetPixelShader(OpenGLPixelShader* InPixelShader);

	OpenGLVertexShader* GetVertexShader() const;
	OpenGLPixelShader* GetPixelShader() const;

	void LinkProgram();
	void DetachShaders();

private:
	OpenGLVertexShader* m_VertexShader;
	OpenGLPixelShader* m_PixelShader;

	GLint m_ProgramID;
};

