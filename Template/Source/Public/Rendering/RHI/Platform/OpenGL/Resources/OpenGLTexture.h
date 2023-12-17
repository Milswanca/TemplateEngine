#pragma once
#include "Rendering/RHI/Resources/RHITexture.h"
#include <glad/glad.h>
#include <unordered_map>

class OpenGLTexture : public RHITexture
{
public:
	struct TexFormatToGLType
	{
		TexFormatToGLType() :
			m_Format(GL_RGBA8),
			m_ChannelLayout(GL_RGBA),
			m_ChannelPrecision(GL_BYTE),
			m_Stride(32)
		{}

		TexFormatToGLType(GLenum InSourceFormat, GLenum InDesiredFormat, GLenum InDataType, unsigned int InStride) :
			m_Format(InSourceFormat),
			m_ChannelLayout(InDesiredFormat),
			m_ChannelPrecision(InDataType),
			m_Stride(InStride)
		{}

		GLenum m_Format;
		GLenum m_ChannelLayout;
		GLenum m_ChannelPrecision;
		unsigned int m_Stride;
	};

	OpenGLTexture(const CreateTextureDesc& InDesc);
	~OpenGLTexture();

	void SetPixelData(unsigned char* InPixels);

protected:
	static std::unordered_map<ETextureTypes, GLenum> s_TexTypeToGLTypes;
	static std::unordered_map<ETextureFormats, TexFormatToGLType> s_TexFormatsToGLFormats;

private:
	GLuint m_TextureID;
	GLenum m_GLTextureType;
	GLenum m_GLTextureFormat;
	GLenum m_GLTextureChannelLayout;
	GLenum m_GLTextureChannelPrecision;
};