#include "Rendering/RHI/Platform/OpenGL/OpenGLRHI.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShader.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLShaderProgram.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLTexture.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLVertexLayout.h"
#include "Rendering/RHI/Platform/OpenGL/Resources/OpenGLBuffer.h"

RHIShaderProgram* OpenGLRHI::RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader)
{
	OpenGLShaderProgram* Program = new OpenGLShaderProgram();
	Program->SetVertexShader(dynamic_cast<OpenGLVertexShader*>(InVertexShader));
	Program->SetPixelShader(dynamic_cast<OpenGLPixelShader*>(InPixelShader));
	Program->LinkProgram();

	return Program;
}

void OpenGLRHI::RHIDeleteShaderProgram(RHIShaderProgram* InProgram)
{
	delete InProgram;
	InProgram = nullptr;
}

RHIVertexShader* OpenGLRHI::RHICreateVertexShader(std::string_view InSource)
{
	OpenGLVertexShader* Shader = new OpenGLVertexShader();
	RHISetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

RHIPixelShader* OpenGLRHI::RHICreatePixelShader(std::string_view InSource)
{
	OpenGLPixelShader* Shader = new OpenGLPixelShader();
	RHISetOpenGLShaderSource(Shader, InSource);
	return Shader;
}

void OpenGLRHI::RHISetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource)
{
	InShader->SetShaderSource(InSource);
	InShader->Compile();
}

void OpenGLRHI::RHIDeleteShader(RHIShader* InShader)
{
	delete InShader;
	InShader = nullptr;
}

RHITexture* OpenGLRHI::RHICreateTexture(const CreateTextureDesc& InDesc)
{
	OpenGLTexture* Texture = new OpenGLTexture(InDesc);
	return Texture;
}

void OpenGLRHI::RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory)
{
	OpenGLTexture* OGLTexture = static_cast<OpenGLTexture*>(InTexture);
	OGLTexture->SetPixelData(InRawMemory);
}

void OpenGLRHI::RHIDeleteTexture(RHITexture* InTexture)
{
	delete InTexture;
	InTexture = nullptr;
}

RHIVertexLayout* OpenGLRHI::RHICreateVertexLayout(const RHIVertexAttributeArray& InAttributes)
{
	return new OpenGLVertexLayout(InAttributes);
}

void OpenGLRHI::RHIBindVertexLayout(RHIVertexLayout* InLayout)
{
	OpenGLVertexLayout* OGLVertexLayout = static_cast<OpenGLVertexLayout*>(InLayout);
	OGLVertexLayout->Bind();
}

RHIVertexBuffer* OpenGLRHI::RHICreateVertexBuffer(const RHIBufferDesc& InDesc)
{
	return new OpenGLVertexBuffer(InDesc);
}

RHIIndexBuffer* OpenGLRHI::RHICreateIndexBuffer(const RHIBufferDesc& InDesc)
{
	return new OpenGLIndexBuffer(InDesc);
}

void OpenGLRHI::RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, unsigned char* InData)
{
	OpenGLBuffer* OGLBuffer = dynamic_cast<OpenGLBuffer*>(InBuffer);
	OGLBuffer->BufferSubData(InSizeBytes, InOffsetBytes, InData);
}