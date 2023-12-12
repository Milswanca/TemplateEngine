#pragma once
#include "Core/Object.h"
#include <unordered_map>
#include <glad/glad.h>

class Texture : public Object
{
public:
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

	struct FTexFormatToGLType
	{
		FTexFormatToGLType() :
			m_SourceFormat(GL_RGBA8),
			m_DesiredFormat(GL_RGBA),
			m_DataType(GL_BYTE),
			m_Stride(32)
		{}

		FTexFormatToGLType(GLenum InSourceFormat, GLenum InDesiredFormat, GLenum InDataType, unsigned int InStride) :
			m_SourceFormat(InSourceFormat),
			m_DesiredFormat(InDesiredFormat),
			m_DataType(InDataType),
			m_Stride(InStride)
		{}

		GLenum m_SourceFormat;
		GLenum m_DesiredFormat;
		GLenum m_DataType;
		unsigned int m_Stride;
	};

	struct FTextureData
	{
	public:
		FTextureData();
		~FTextureData();

		unsigned char* m_Data;
		int m_Width;
		int m_Height;
		int m_Depth;
		bool m_bGenerateMips;
		ETextureFormats m_Format;
	};

protected:
	IMPLEMENT_CONSTRUCTOR(Texture, Object);

	virtual void Begin() override;
	virtual void End() override;

public:
	FTextureData* GetTextureData() const;
	unsigned int GetTextureID() const;

	virtual void Build() = 0;

protected:
	static std::unordered_map<ETextureFormats, FTexFormatToGLType> s_TexFormatsToGLTypes;

private:
	unsigned int m_TextureID;
	FTextureData* m_RenderData;
};

