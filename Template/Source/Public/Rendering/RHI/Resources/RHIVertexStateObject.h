#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"
#include "Rendering/RHI/Resources/RHIVertexAttributes.h"

class RHIVertexBuffer;
class RHIIndexBuffer;

class RHIVertexStateObject : RHIResource
{
public:
	RHIVertexStateObject() = delete;
	RHIVertexStateObject(RHIVertexBuffer* InVertexBuffer, RHIIndexBuffer* InIndexBuffer, const RHIVertexAttributeArray& InAttributeLayout);

	void SetVertexBuffer(RHIVertexBuffer* InVertexBuffer);
	void SetIndexBuffer(RHIIndexBuffer* InIndexBuffer);

	void SetAttribute(int InLocation, const RHIVertexAttributeDesc& InDesc);
	const RHIVertexAttributeDesc& GetAttribute(int InLocation);
	int GetNumAttributes() const;
	
	RHIVertexBuffer* GetVertexBuffer() const;
	RHIIndexBuffer* GetIndexBuffer() const;

private:
	RHIVertexBuffer* m_VertexBuffer;
	RHIIndexBuffer* m_IndexBuffer;
	RHIVertexAttributeArray m_VertexAttributes;
};