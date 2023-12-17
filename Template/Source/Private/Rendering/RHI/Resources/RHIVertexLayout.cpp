#include "Rendering/RHI/Resources/RHIVertexLayout.h"

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
