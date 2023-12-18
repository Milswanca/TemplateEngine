#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"

struct RHIBufferDesc
{
	RHIBufferDesc() {}
	RHIBufferDesc(unsigned int InSize, unsigned int InStride);

	unsigned int m_Size;
	unsigned int m_Stride;
};

class RHIBuffer : public RHIResource
{
public:
	RHIBuffer() = delete;
	RHIBuffer(const RHIBufferDesc& InDesc);
	virtual ~RHIBuffer() {};

	const RHIBufferDesc& GetDescription() const;

private:
	RHIBufferDesc m_Description;
};

class RHIVertexBuffer : public virtual RHIBuffer
{
public:
	RHIVertexBuffer(const RHIBufferDesc& InDesc) : RHIBuffer(InDesc) {}
};

class RHIIndexBuffer : public virtual RHIBuffer
{
public:
	RHIIndexBuffer(const RHIBufferDesc& InDesc) : RHIBuffer(InDesc) {}
};