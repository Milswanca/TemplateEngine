#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"
#include <string>
#include <vector>

enum class VertexAttributeTypes
{
	Float,
	Int,
};

struct RHIVertexAttributeDesc
{
	RHIVertexAttributeDesc() = default;
	RHIVertexAttributeDesc(std::string InName, VertexAttributeTypes InType, int InNumChannels, bool InNormalize, int InStride, int InOffset);
	RHIVertexAttributeDesc(const RHIVertexAttributeDesc& InCopy);
	RHIVertexAttributeDesc(RHIVertexAttributeDesc&& InOther) noexcept;
	RHIVertexAttributeDesc& operator=(RHIVertexAttributeDesc InOther);
	friend void swap(RHIVertexAttributeDesc& InFirst, RHIVertexAttributeDesc& InSecond) noexcept;

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
	RHIVertexAttributeArray() = delete;
	RHIVertexAttributeArray(int InSize);
	RHIVertexAttributeArray(const RHIVertexAttributeArray& InCopy);
	RHIVertexAttributeArray(RHIVertexAttributeArray&& InOther) noexcept;
	RHIVertexAttributeArray& operator=(RHIVertexAttributeArray InOther);
	friend void swap(RHIVertexAttributeArray& InFirst, RHIVertexAttributeArray& InSecond) noexcept;
	~RHIVertexAttributeArray();

	void SetAttribute(int InIndex, const RHIVertexAttributeDesc& InAttribute);
	const RHIVertexAttributeDesc& GetAttribute(int InIndex);
	int GetNumAttributes() const;

private:
	int m_NumAttributes;
	RHIVertexAttributeDesc* m_Attributes;
};
