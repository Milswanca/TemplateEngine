#include "Rendering/RHI/Resources/RHIVertexLayout.h"

RHIVertexAttributeDesc::RHIVertexAttributeDesc()
{

}

RHIVertexAttributeDesc::RHIVertexAttributeDesc(const std::string& InName, VertexAttributeTypes InType, int InNumChannels, bool InNormalize, int InStride, int InOffset)
{
	m_Name = InName;
	m_Type = InType;
	m_Stride = InStride;
	m_NumChannels = InNumChannels;
	m_bNormalize = InNormalize;
	m_Offset = InOffset;
}

RHIVertexAttributeArray::RHIVertexAttributeArray(const RHIVertexAttributeArray& InCopy)
{
	m_NumAttributes = InCopy.m_NumAttributes;
	m_Attributes = new RHIVertexAttributeDesc[m_NumAttributes];

	memcpy(m_Attributes, InCopy.m_Attributes, sizeof(RHIVertexAttributeDesc) * m_NumAttributes);
}

RHIVertexAttributeArray::RHIVertexAttributeArray(int InSize)
{
	m_NumAttributes = InSize;
	m_Attributes = new RHIVertexAttributeDesc[InSize];
}

RHIVertexAttributeArray::~RHIVertexAttributeArray()
{
	delete[] m_Attributes;
	m_Attributes = nullptr;
}

void RHIVertexAttributeArray::SetAttribute(int InIndex, const RHIVertexAttributeDesc& InAttribute)
{
	memcpy(&m_Attributes[InIndex], &InAttribute, sizeof(RHIVertexAttributeDesc));
}

const RHIVertexAttributeDesc& RHIVertexAttributeArray::GetAttribute(int InIndex)
{
	return m_Attributes[InIndex];
}

int RHIVertexAttributeArray::GetNumAttributes() const
{
	return m_NumAttributes;
}

RHIVertexLayout::RHIVertexLayout(const RHIVertexAttributeArray& InAttributes) : m_Attributes(InAttributes)
{

}

RHIVertexLayout::~RHIVertexLayout()
{

}

const RHIVertexAttributeDesc& RHIVertexLayout::GetAttribute(int InLocation)
{
	return m_Attributes.GetAttribute(InLocation);
}

int RHIVertexLayout::GetNumAttributes() const
{
	return m_Attributes.GetNumAttributes();
}
