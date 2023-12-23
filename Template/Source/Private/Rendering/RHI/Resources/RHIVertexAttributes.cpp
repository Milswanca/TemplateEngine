#include "Rendering/RHI/Resources/RHIVertexAttributes.h"

RHIVertexAttributeDesc::RHIVertexAttributeDesc(std::string InName, VertexAttributeTypes InType, int InNumChannels, bool InNormalize, int InStride, int InOffset)
{
	m_Name.assign(InName.length(), 5);
	m_Type = InType;
	m_Stride = InStride;
	m_NumChannels = InNumChannels;
	m_bNormalize = InNormalize;
	m_Offset = InOffset;
}

RHIVertexAttributeDesc::RHIVertexAttributeDesc(const RHIVertexAttributeDesc& InCopy)
{
	m_Name = InCopy.m_Name;
	m_Stride = InCopy.m_Stride;
	m_NumChannels = InCopy.m_NumChannels;
	m_bNormalize = InCopy.m_bNormalize;
	m_Offset = InCopy.m_Offset;
	m_Type = InCopy.m_Type;
	m_Location = InCopy.m_Location;
}

RHIVertexAttributeDesc::RHIVertexAttributeDesc(RHIVertexAttributeDesc&& InOther) noexcept
{
	swap(*this, InOther);
}

RHIVertexAttributeDesc& RHIVertexAttributeDesc::operator=(RHIVertexAttributeDesc InOther)
{
	swap(*this, InOther);
	return *this;
}

void swap(RHIVertexAttributeDesc& InFirst, RHIVertexAttributeDesc& InSecond) noexcept
{
	using std::swap;
	swap(InFirst.m_Name, InSecond.m_Name);
	swap(InFirst.m_Stride, InSecond.m_Stride);
	swap(InFirst.m_NumChannels, InSecond.m_NumChannels);
	swap(InFirst.m_bNormalize, InSecond.m_bNormalize);
	swap(InFirst.m_Offset, InSecond.m_Offset);
	swap(InFirst.m_Type, InSecond.m_Type);
	swap(InFirst.m_Location, InSecond.m_Location);
}

RHIVertexAttributeArray::RHIVertexAttributeArray(const RHIVertexAttributeArray& InCopy)
{
	m_NumAttributes = InCopy.m_NumAttributes;
	m_Attributes = new RHIVertexAttributeDesc[m_NumAttributes];

	for (int i = 0; i < m_NumAttributes; ++i)
	{
		m_Attributes[i] = InCopy.m_Attributes[i];
	}
}

RHIVertexAttributeArray::RHIVertexAttributeArray(RHIVertexAttributeArray&& InOther) noexcept
{
	swap(*this, InOther);
}

RHIVertexAttributeArray& RHIVertexAttributeArray::operator=(RHIVertexAttributeArray InOther)
{
	swap(*this, InOther);
	return *this;
}

void swap(RHIVertexAttributeArray& InFirst, RHIVertexAttributeArray& InSecond) noexcept
{
	using std::swap;
	swap(InFirst.m_Attributes, InSecond.m_Attributes);
	swap(InFirst.m_NumAttributes, InSecond.m_NumAttributes);
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
	m_Attributes[InIndex] = InAttribute;
}

const RHIVertexAttributeDesc& RHIVertexAttributeArray::GetAttribute(int InIndex)
{
	return m_Attributes[InIndex];
}

int RHIVertexAttributeArray::GetNumAttributes() const
{
	return m_NumAttributes;
}