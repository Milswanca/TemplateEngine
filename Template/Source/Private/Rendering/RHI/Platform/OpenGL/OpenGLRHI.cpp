#include "Rendering/RHI/Platform/OpenGL/OpenGLRHI.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShader.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShaderProgram.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLTexture.h"

RHIShaderProgram* OpenGLRHI::CreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader)
{
	OpenGLShaderProgram* Program = new OpenGLShaderProgram();
	Program->SetVertexShader(ResourceCast<OpenGLVertexShader>(InVertexShader));
	Program->SetPixelShader(ResourceCast<OpenGLPixelShader>(InPixelShader));
	Program->LinkProgram();

	return Program;
}

void OpenGLRHI::DeleteShaderProgram(RHIShaderProgram* InProgram)
{
	delete InProgram;
	InProgram = nullptr;
}

RHIVertexShader* OpenGLRHI::CreateVertexShader(std::string_view InSource)
{
	OpenGLVertexShader* Shader = new OpenGLVertexShader();
	SetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

RHIPixelShader* OpenGLRHI::CreatePixelShader(std::string_view InSource)
{
	OpenGLPixelShader* Shader = new OpenGLPixelShader();
	SetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

void OpenGLRHI::SetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource)
{
	InShader->SetShaderSource(InSource);
	InShader->Compile();
}

void OpenGLRHI::DeleteShader(RHIShader* InShader)
{
	delete InShader;
	InShader = nullptr;
}

RHITexture* OpenGLRHI::CreateTexture(const CreateTextureDesc& InDesc)
{
	OpenGLTexture* Texture = new OpenGLTexture(InDesc);
	return Texture;
}

void OpenGLRHI::SetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory)
{
	OpenGLTexture* OGLTexture = ResourceCast<OpenGLTexture>(InTexture);
	OGLTexture->SetPixelData(InRawMemory);
}

void OpenGLRHI::DestroyTexture(RHITexture* InTexture)
{
	delete InTexture;
	InTexture = nullptr;
}
