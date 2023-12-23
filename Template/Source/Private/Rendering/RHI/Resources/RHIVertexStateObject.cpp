#include "Rendering/RHI/Resources/RHIVertexStateObject.h"

RHIVertexStateObject::RHIVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributes)
    : m_VertexBuffer(InVertexBuffer), m_IndexBuffer(InIndexBuffer), m_VertexAttributes(InAttributes)
{
}

void RHIVertexStateObject::SetVertexBuffer(RHIVertexBuffer* InVertexBuffer)
{
    m_VertexBuffer = InVertexBuffer;
}

void RHIVertexStateObject::SetIndexBuffer(RHIIndexBuffer* InIndexBuffer)
{
    m_IndexBuffer = InIndexBuffer;
}

void RHIVertexStateObject::SetAttribute(int InLocation, const RHIVertexAttributeDesc& InDesc)
{
    m_VertexAttributes.SetAttribute(InLocation, InDesc);
}

const RHIVertexAttributeDesc& RHIVertexStateObject::GetAttribute(int InLocation)
{
    return m_VertexAttributes.GetAttribute(InLocation);
}

int RHIVertexStateObject::GetNumAttributes() const
{
    return m_VertexAttributes.GetNumAttributes();
}

RHIVertexBuffer* RHIVertexStateObject::GetVertexBuffer() const
{
    return m_VertexBuffer;
}

RHIIndexBuffer* RHIVertexStateObject::GetIndexBuffer() const
{
    return m_IndexBuffer;
}