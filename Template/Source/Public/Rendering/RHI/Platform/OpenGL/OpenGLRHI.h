#pragma once
#include "Rendering/RHI/RHI.h"

class OpenGLShader;

class OpenGLRHI : public RHI
{

public:
	RHIShaderProgram* CreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) override;
	void DeleteShaderProgram(RHIShaderProgram* InProgram) override;

	RHIVertexShader* CreateVertexShader(std::string_view InSource) override;
	RHIPixelShader* CreatePixelShader(std::string_view InSource) override;
	void SetOpenGLShaderSource(OpenGLShader* InShader, std::string_view InSource);
	void DeleteShader(RHIShader* InShader) override;

	RHITexture* CreateTexture(const CreateTextureDesc& InDesc) override;
	void SetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) override;
	void DestroyTexture(RHITexture* InTexture) override;
};