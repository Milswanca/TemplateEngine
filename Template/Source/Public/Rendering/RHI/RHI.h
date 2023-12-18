#pragma once
#include "Rendering/RHI/Resources/RHIShader.h"
#include "Rendering/RHI/Resources/RHIShaderProgram.h"
#include "Rendering/RHI/Resources/RHITexture.h"
#include "Rendering/RHI/Resources/RHIVertexLayout.h"
#include "Rendering/RHI/Resources/RHIBuffer.h"
#include <glm/glm.hpp>
#include <string_view>

// Global RHI Pointer
extern class RHI* s_RHI;

class RHI
{
public:
	virtual RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) = 0;
	virtual void RHIDeleteShaderProgram(RHIShaderProgram* InProgram) = 0;

	virtual RHIVertexShader* RHICreateVertexShader(std::string_view InSource) = 0;
	virtual RHIPixelShader* RHICreatePixelShader(std::string_view InSource) = 0;
	virtual void RHIDeleteShader(RHIShader* InShader) = 0;

	virtual RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc) = 0;
	virtual void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) = 0;
	virtual void RHIDeleteTexture(RHITexture* InTexture) = 0;

	virtual RHIVertexLayout* RHICreateVertexLayout(const RHIVertexAttributeArray& InAttributes) = 0;
	virtual void RHIBindVertexLayout(RHIVertexLayout* InLayout) = 0;

	virtual RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc) = 0;
	virtual RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc) = 0;
	virtual void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, unsigned char* InData) = 0;
};

inline RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader)
{
	return s_RHI->RHICreateShaderProgram(InVertexShader, InPixelShader);
}

inline void RHIDeleteShaderProgram(RHIShaderProgram* InProgram)
{
	s_RHI->RHIDeleteShaderProgram(InProgram);
}

inline RHIVertexShader* RHICreateVertexShader(std::string_view InSource)
{
	return s_RHI->RHICreateVertexShader(InSource);
}

inline RHIPixelShader* RHICreatePixelShader(std::string_view InSource)
{
	return s_RHI->RHICreatePixelShader(InSource);
}

inline void RHIDeleteShader(RHIShader* InShader)
{
	s_RHI->RHIDeleteShader(InShader);
}

inline RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc)
{
	return s_RHI->RHICreateTexture(InDesc);
}

inline void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory)
{
	s_RHI->RHISetTexturePixels(InTexture, InRawMemory);
}

inline void RHIDeleteTexture(RHITexture* InTexture)
{
	s_RHI->RHIDeleteTexture(InTexture);
}

inline RHIVertexLayout* RHICreateVertexLayout(const RHIVertexAttributeArray& InAttributes)
{
	return s_RHI->RHICreateVertexLayout(InAttributes);
}

inline void RHIBindVertexLayout(RHIVertexLayout* InLayout)
{
	s_RHI->RHIBindVertexLayout(InLayout);
}

inline RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc)
{
	return s_RHI->RHICreateVertexBuffer(InDesc);
}

inline RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc)
{
	return s_RHI->RHICreateIndexBuffer(InDesc);
}

inline void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, unsigned char* InData)
{
	s_RHI->RHIUpdateBufferData(InBuffer, InSizeBytes, InOffsetBytes, InData);
}

inline void RHISetIndexBufferIndices(RHIIndexBuffer* InIndexBuffer, int InNumIndices, int* InIndices)
{
	s_RHI->RHIUpdateBufferData(InIndexBuffer, InNumIndices * sizeof(int), 0, (unsigned char*)InIndices);
}

template<typename ToType = RHIResource>
inline ToType* ResourceCast(RHIResource* InResource)
{
	return static_cast<ToType*>(InResource);
}