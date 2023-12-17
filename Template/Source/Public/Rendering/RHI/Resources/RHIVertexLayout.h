#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"
#include "Rendering/RHI/Resources/RHIVertexAttribute.h"

class RHIVertexLayout : public RHIResource
{
public:
	RHIVertexLayout() = delete;
	RHIVertexLayout(const RHIVertexAttributeArray& InAttributes);
	~RHIVertexLayout();

	const RHIVertexAttributeDesc& GetAttribute(int InLocation);
	int GetNumAttributes() const;

protected:

private:
	RHIVertexAttributeArray m_Attributes;
};

