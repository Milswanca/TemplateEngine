#pragma once
#include <string>
#include <unordered_map>

enum class VertexAttributeTypes
{
	Float,
	Int,
};

struct RHIVertexAttributeDesc
{
	RHIVertexAttributeDesc()
	{

	}

	RHIVertexAttributeDesc(const std::string& InName, VertexAttributeTypes InType, int InNumChannels, bool InNormalize, int InStride, int InOffset)
	{
		m_Name = InName;
		m_Type = InType;
		m_Stride = InStride;
		m_NumChannels = InNumChannels;
		m_bNormalize = InNormalize;
		m_Offset = InOffset;
	}

	std::string m_Name;
	unsigned int m_Stride;
	unsigned int m_NumChannels;
	bool m_bNormalize;
	int m_Offset;
	VertexAttributeTypes m_Type;
	int m_Location;
};

struct RHIVertexAttributeArray
{
	RHIVertexAttributeArray(const RHIVertexAttributeArray& InCopy)
	{
		m_NumAttributes = InCopy.m_NumAttributes;
		m_Attributes = new RHIVertexAttributeDesc[m_NumAttributes];

		memcpy(m_Attributes, InCopy.m_Attributes, sizeof(RHIVertexAttributeDesc) * m_NumAttributes);
	}

	RHIVertexAttributeArray(int InSize)
	{
		m_NumAttributes = InSize;
		m_Attributes = new RHIVertexAttributeDesc[InSize];
	}

	~RHIVertexAttributeArray()
	{
		delete[] m_Attributes;
		m_Attributes = nullptr;
	}

	void SetAttribute(int InIndex, const RHIVertexAttributeDesc& InAttribute)
	{
		memcpy(&m_Attributes[InIndex], &InAttribute, sizeof(RHIVertexAttributeDesc));
	}

	const RHIVertexAttributeDesc& GetAttribute(int InIndex)
	{
		return m_Attributes[InIndex];
	}

	int GetNumAttributes() const
	{
		return m_NumAttributes;
	}

private:
	int m_NumAttributes;
	RHIVertexAttributeDesc* m_Attributes;
};