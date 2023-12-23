#include "Platform/OpenGL/RHI/Resources/OpenGLTexture.h"

std::unordered_map<ETextureTypes, GLenum> OpenGLTexture::s_TexTypeToGLTypes
{
	{ ETextureTypes::Texture1D, GL_TEXTURE_1D },
	{ ETextureTypes::Texture2D, GL_TEXTURE_2D },
	{ ETextureTypes::Texture3D, GL_TEXTURE_3D },
};

std::unordered_map<ETextureFormats, OpenGLTexture::TexFormatToGLType> OpenGLTexture::s_TexFormatsToGLFormats
{
	{ ETextureFormats::RGBA8, OpenGLTexture::TexFormatToGLType(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, sizeof(char) * 4)},
	{ ETextureFormats::RGBA16, OpenGLTexture::TexFormatToGLType(GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, sizeof(short) * 4) },
	{ ETextureFormats::RGBA32, OpenGLTexture::TexFormatToGLType(GL_RGBA32F, GL_RGBA, GL_FLOAT, sizeof(float) * 4) },
	{ ETextureFormats::RGB8, OpenGLTexture::TexFormatToGLType(GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, sizeof(char) * 3) },
	{ ETextureFormats::RGB16, OpenGLTexture::TexFormatToGLType(GL_RGB16F, GL_RGB, GL_HALF_FLOAT, sizeof(short) * 3) },
	{ ETextureFormats::RGB32, OpenGLTexture::TexFormatToGLType(GL_RGB32F, GL_RGB, GL_FLOAT, sizeof(float) * 3) },
	{ ETextureFormats::RG8, OpenGLTexture::TexFormatToGLType(GL_RG8, GL_RG, GL_UNSIGNED_BYTE, sizeof(char) * 2) },
	{ ETextureFormats::RG16, OpenGLTexture::TexFormatToGLType(GL_RG16F, GL_RG, GL_HALF_FLOAT, sizeof(short) * 2) },
	{ ETextureFormats::RG32, OpenGLTexture::TexFormatToGLType(GL_RG32F, GL_RG, GL_FLOAT, sizeof(float) * 2) },
	{ ETextureFormats::R8, OpenGLTexture::TexFormatToGLType(GL_R8, GL_RED, GL_UNSIGNED_BYTE, sizeof(char) * 1) },
	{ ETextureFormats::R16, OpenGLTexture::TexFormatToGLType(GL_R16F, GL_RED, GL_HALF_FLOAT, sizeof(short) * 1) },
	{ ETextureFormats::R32, OpenGLTexture::TexFormatToGLType(GL_R32F, GL_RED, GL_FLOAT, sizeof(float) * 1) },
	{ ETextureFormats::Depth, OpenGLTexture::TexFormatToGLType(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, sizeof(float) * 1) },
};

OpenGLTexture::OpenGLTexture(const CreateTextureDesc& InDesc) : RHITexture(InDesc)
{
	m_GLTextureType = s_TexTypeToGLTypes[InDesc.m_Type];
	m_GLTextureFormat = s_TexFormatsToGLFormats[InDesc.m_Format].m_Format;
	m_GLTextureChannelLayout = s_TexFormatsToGLFormats[InDesc.m_Format].m_ChannelLayout;
	m_GLTextureChannelPrecision = s_TexFormatsToGLFormats[InDesc.m_Format].m_ChannelPrecision;

	m_TextureID = 0;
	glGenTextures(1, &m_TextureID);
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &m_TextureID);
}

void OpenGLTexture::SetPixelData(unsigned char* InPixels)
{
	const TextureDesc Description = GetTextureDescription();

	glBindTexture(m_GLTextureType, m_TextureID);
	
	switch (m_GLTextureType)
	{
	case GL_TEXTURE_2D:
		glTexImage2D(m_GLTextureType, 0, m_GLTextureFormat, Description.m_Width, Description.m_Height, 0, m_GLTextureChannelLayout, m_GLTextureChannelPrecision, InPixels);
		break;
	}
}