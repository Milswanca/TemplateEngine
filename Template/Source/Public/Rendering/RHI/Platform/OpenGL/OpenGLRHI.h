#pragma once
#include "Rendering/RHI/RHI.h"

class OpenGLShader;

class OpenGLRHI : public RHI
{
public:
	RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) override;
	void RHIDeleteShaderProgram(RHIShaderProgram* InProgram) override;

	RHIVertexShader* RHICreateVertexShader(std::string_view InSource) override;
	RHIPixelShader* RHICreatePixelShader(std::string_view InSource) override;
	void RHISetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource);
	void RHIDeleteShader(RHIShader* InShader) override;

	RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc) override;
	void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) override;
	void RHIDeleteTexture(RHITexture* InTexture) override;

	RHIVertexLayout* RHICreateVertexLayout(const RHIVertexAttributeArray& InAttributes) override;
	void RHIBindVertexLayout(RHIVertexLayout* InLayout) override;

	RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc) override;
	RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc) override;
	void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, unsigned char* InData) override;
};