#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"

enum class EShaderTypes
{
	Unknown,
	Vertex,
	Pixel,
	TessControl,
	TessEval,
	COUNT
};

class RHIShader : public RHIResource
{
public:
	RHIShader() = delete;
	RHIShader(EShaderTypes InType) : m_Type(InType) {}
	virtual ~RHIShader() = default;

	EShaderTypes GetType() const { return m_Type; }

private:
	EShaderTypes m_Type;
};

class RHIPixelShader : public virtual RHIShader
{
public:
	RHIPixelShader() : RHIShader(EShaderTypes::Pixel) {};
};

class RHIVertexShader : public virtual RHIShader
{
public:
	RHIVertexShader() : RHIShader(EShaderTypes::Vertex) {};
};