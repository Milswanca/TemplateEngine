#pragma once
#include "Rendering/RHI/Resources/RHIShader.h"
#include "Rendering/RHI/Resources/RHIShaderProgram.h"
#include "Rendering/RHI/Resources/RHITexture.h"
#include "Rendering/RHI/Resources/RHIVertexLayout.h"
#include <glm/glm.hpp>
#include <string_view>

class RHI
{
public:
	virtual RHIShaderProgram* CreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) = 0;
	virtual void DeleteShaderProgram(RHIShaderProgram* InProgram) = 0;

	virtual RHIVertexShader* CreateVertexShader(std::string_view InSource) = 0;
	virtual RHIPixelShader* CreatePixelShader(std::string_view InSource) = 0;
	virtual void DeleteShader(RHIShader* InShader) = 0;

	virtual RHITexture* CreateTexture(const CreateTextureDesc& InDesc) = 0;
	virtual void SetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) = 0;
	virtual void DestroyTexture(RHITexture* InTexture) = 0;

	virtual RHIVertexLayout* CreateVertexLayout() = 0;
	virtual void BindVertexLayout(RHIVertexLayout* InLayout) = 0;
};

template<typename ToType = RHIResource>
ToType* ResourceCast(RHIResource* InResource)
{
	return static_cast<ToType*>(InResource);
}