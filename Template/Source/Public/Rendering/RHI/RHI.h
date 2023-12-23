#pragma once
#include "Rendering/RHI/Resources/RHIShader.h"
#include "Rendering/RHI/Resources/RHIShaderProgram.h"
#include "Rendering/RHI/Resources/RHITexture.h"
#include "Rendering/RHI/Resources/RHIVertexAttributes.h"
#include "Rendering/RHI/Resources/RHIVertexStateObject.h"
#include "Rendering/RHI/Resources/RHIBuffer.h"
#include <glm/glm.hpp>
#include <string_view>

enum class BufferTypes
{
	ColorBuffer,
	DepthBuffer
};

// Global RHI Pointer
extern class RHI* s_RHI;
extern class RHI* CreateRHI();

class RHI
{
public:
	virtual void RHISetViewport(int InX, int InY, int InWidth, int InHeight) = 0;
	virtual void RHIBeginFrame() = 0;
	virtual void RHIEndFrame() = 0;
	virtual void RHIDrawElements(int InNumIndices, int InOffset) = 0;
	
	virtual RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader) = 0;
	virtual void RHIUseShaderProgram(RHIShaderProgram* InProgram) = 0;
	virtual void RHIDeleteShaderProgram(RHIShaderProgram* InProgram) = 0;

	virtual RHIVertexShader* RHICreateVertexShader(std::string_view InSource) = 0;
	virtual RHIPixelShader* RHICreatePixelShader(std::string_view InSource) = 0;
	virtual void RHIDeleteShader(RHIShader* InShader) = 0;

	virtual RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc) = 0;
	virtual void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory) = 0;
	virtual void RHIDeleteTexture(RHITexture* InTexture) = 0;
		
	virtual RHIVertexStateObject* RHICreateVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes) = 0;
	virtual void RHIRebuildVertexStateObject(RHIVertexStateObject* InStateObject) = 0;
	virtual void RHIBindVertexStateObject(RHIVertexStateObject* InStateObject) = 0;
	virtual void RHIDeleteVertexStateObject(RHIVertexStateObject* InStateObject) = 0;
	virtual RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc) = 0;
	virtual RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc) = 0;
	virtual void RHIBindBuffer(RHIBuffer* InBuffer) = 0;
	virtual void* RHIMapBuffer(RHIBuffer* InBuffer, BufferAccessTypes InAccess) = 0;
	virtual void RHIUnmapBuffer(RHIBuffer* InBuffer) = 0;
	virtual void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, void* InData) = 0;
	virtual void RHIDeleteBuffer(RHIBuffer* InBuffer) = 0;
};

inline void RHISetViewport(int InX, int InY, int InWidth, int InHeight)
{
	s_RHI->RHISetViewport(InX, InY, InWidth, InHeight);	
}

inline void RHIBeginFrame()
{
	s_RHI->RHIBeginFrame();
}

inline void RHIEndFrame()
{
	s_RHI->RHIEndFrame();
}

inline void RHIDrawElements(int InNumElements, int InOffset)
{
	return s_RHI->RHIDrawElements(InNumElements, InOffset);
}

inline RHIShaderProgram* RHICreateShaderProgram(RHIVertexShader* InVertexShader, RHIPixelShader* InPixelShader)
{
	return s_RHI->RHICreateShaderProgram(InVertexShader, InPixelShader);
}

inline void RHIUseShaderProgram(RHIShaderProgram* InProgram)
{
	if(InProgram)
	{
		s_RHI->RHIUseShaderProgram(InProgram);
	}
}

inline void RHIDeleteShaderProgram(RHIShaderProgram* InProgram)
{
	if(InProgram)
	{
		s_RHI->RHIDeleteShaderProgram(InProgram);
	}
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
	if(InShader)
	{
		s_RHI->RHIDeleteShader(InShader);
	}
}

inline RHITexture* RHICreateTexture(const CreateTextureDesc& InDesc)
{
	return s_RHI->RHICreateTexture(InDesc);
}

inline void RHISetTexturePixels(RHITexture* InTexture, unsigned char* InRawMemory)
{
	if(InTexture)
	{
		s_RHI->RHISetTexturePixels(InTexture, InRawMemory);
	}
}

inline void RHIDeleteTexture(RHITexture* InTexture)
{
	if(InTexture)
	{
		s_RHI->RHIDeleteTexture(InTexture);
	}
}

inline RHIVertexStateObject* RHICreateVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes)
{
	return s_RHI->RHICreateVertexStateObject(InVertexBuffer, InIndexBuffer, InAttributes);
}

inline void RHIRebuildVertexStateObject(RHIVertexStateObject* InStateObject)
{
	if(InStateObject)
	{
		s_RHI->RHIRebuildVertexStateObject(InStateObject);
	}
}

inline void RHIBindVertexStateObject(RHIVertexStateObject* InStateObject)
{
	if(InStateObject)
	{
		s_RHI->RHIBindVertexStateObject(InStateObject);
	}
}

inline void RHIDeleteVertexStateObject(RHIVertexStateObject* InStateObject)
{
	if(InStateObject)
	{
		s_RHI->RHIDeleteVertexStateObject(InStateObject);
	}
}

inline RHIVertexBuffer* RHICreateVertexBuffer(const RHIBufferDesc& InDesc)
{
	return s_RHI->RHICreateVertexBuffer(InDesc);
}

inline RHIIndexBuffer* RHICreateIndexBuffer(const RHIBufferDesc& InDesc)
{
	return s_RHI->RHICreateIndexBuffer(InDesc);
}

inline void RHIBindBuffer(RHIBuffer* InBuffer)
{
	if(InBuffer)
	{
		s_RHI->RHIBindBuffer(InBuffer);
	}
}

inline void* RHIMapBuffer(RHIBuffer* InBuffer, BufferAccessTypes InAccess)
{
	if(InBuffer)
	{
		return s_RHI->RHIMapBuffer(InBuffer, InAccess);
	}

	return nullptr;
}

inline void RHIUnmapBuffer(RHIBuffer* InBuffer)
{
	if(InBuffer)
	{
		s_RHI->RHIUnmapBuffer(InBuffer);
	}
}

inline void RHIUpdateBufferData(RHIBuffer* InBuffer, int InSizeBytes, int InOffsetBytes, void* InData)
{
	if(InBuffer)
	{
		s_RHI->RHIUpdateBufferData(InBuffer, InSizeBytes, InOffsetBytes, InData);
	}
}

inline void RHISetIndexBufferIndices(RHIIndexBuffer* InIndexBuffer, int InNumIndices, unsigned int* InIndices)
{
	if(InIndexBuffer)
	{
		s_RHI->RHIUpdateBufferData(InIndexBuffer, InNumIndices * sizeof(int), 0, (unsigned char*)InIndices);
	}
}

inline void RHIDeleteBuffer(RHIBuffer* InBuffer)
{
	if(InBuffer)
	{
		s_RHI->RHIDeleteBuffer(InBuffer);
	}
}

template<typename ToType = RHIResource>
inline ToType* ResourceCast(RHIResource* InResource)
{
	return static_cast<ToType*>(InResource);
}