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
	virtual ~RHIShader() {}

	EShaderTypes GetType() const { return m_Type; }

private:
	EShaderTypes m_Type;
};

class RHIPixelShader : public RHIShader
{
public:
	RHIPixelShader() : RHIShader(EShaderTypes::Pixel) {};
};

class RHIVertexShader : public RHIShader
{
public:
	RHIVertexShader() : RHIShader(EShaderTypes::Vertex) {};
};