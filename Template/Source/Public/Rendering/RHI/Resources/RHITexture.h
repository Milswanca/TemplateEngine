#pragma once
#include "Rendering/RHI/Resources/RHIResource.h"

enum class ETextureFormats
{
	R8,
	RG8,
	RGB8,
	RGBA8,
	R16,
	RG16,
	RGB16,
	RGBA16,
	R32,
	RG32,
	RGB32,
	RGBA32,
	Depth
};

enum class ETextureTypes
{
	Texture1D,
	Texture2D,
	Texture3D
};

struct TextureDesc
{
public:
	short m_Width;
	short m_Height;
	short m_Depth;
	ETextureFormats m_Format;
	ETextureTypes m_Type;
};

struct CreateTextureDesc : public TextureDesc
{
	void CreateTexture1D(short InWidth, ETextureFormats InTextureFormat)
	{
		m_Width = InWidth;
		m_Format = InTextureFormat;
		m_Type = ETextureTypes::Texture1D;
	}

	void CreateTexture2D(short InWidth, short InHeight, ETextureFormats InTextureFormat)
	{
		m_Width = InWidth;
		m_Height = InHeight;
		m_Format = InTextureFormat;
		m_Type = ETextureTypes::Texture2D;
	}

	void CreateTexture3D(short InWidth, short InHeight, short InDepth, ETextureFormats InTextureFormat)
	{
		m_Width = InWidth;
		m_Height = InHeight;
		m_Depth = InDepth;
		m_Format = InTextureFormat;
		m_Type = ETextureTypes::Texture3D;
	}
};

class RHITexture : public RHIResource
{
public:
	RHITexture(const CreateTextureDesc& InData)
	{
		m_TextureDescription = InData;
	}

	const TextureDesc& GetTextureDescription() const
	{
		return m_TextureDescription;
	}

private:
	TextureDesc m_TextureDescription;
};