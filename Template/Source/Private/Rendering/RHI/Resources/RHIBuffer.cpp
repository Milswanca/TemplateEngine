#include "Rendering/RHI/Resources/RHIBuffer.h"

RHIBufferDesc::RHIBufferDesc(unsigned int InSize, unsigned int InStride)
{
	m_Size = InSize;
	m_Stride = InStride;
}

RHIBuffer::RHIBuffer(const RHIBufferDesc& InDesc)
{
	m_Description = InDesc;
}

const RHIBufferDesc& RHIBuffer::GetDescription() const
{
	return m_Description;
}