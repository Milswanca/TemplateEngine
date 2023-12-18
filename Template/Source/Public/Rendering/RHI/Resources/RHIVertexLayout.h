#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"
#include <string>

enum class VertexAttributeTypes
{
	Float,
	Int,
};

struct RHIVertexAttributeDesc
{
	RHIVertexAttributeDesc();
	RHIVertexAttributeDesc(const std::string& InName, VertexAttributeTypes InType, int InNumChannels, bool InNormalize, int InStride, int InOffset);

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
	RHIVertexAttributeArray(const RHIVertexAttributeArray& InCopy);
	RHIVertexAttributeArray(int InSize);
	~RHIVertexAttributeArray();

	void SetAttribute(int InIndex, const RHIVertexAttributeDesc& InAttribute);
	const RHIVertexAttributeDesc& GetAttribute(int InIndex);
	int GetNumAttributes() const;

private:
	int m_NumAttributes;
	RHIVertexAttributeDesc* m_Attributes;
};

class RHIVertexLayout : public RHIResource
{
public:
	RHIVertexLayout() = delete;
	RHIVertexLayout(const RHIVertexAttributeArray& InAttributes);
	~RHIVertexLayout();

	const RHIVertexAttributeDesc& GetAttribute(int InLocation);
	int GetNumAttributes() const;

private:
	RHIVertexAttributeArray m_Attributes;
};

