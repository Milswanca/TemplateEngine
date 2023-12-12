#include "Rendering/Texture.h"

std::unordered_map<Texture::ETextureFormats, Texture::FTexFormatToGLType> Texture::s_TexFormatsToGLTypes
{
	{Texture::ETextureFormats::RGBA8, Texture::FTexFormatToGLType(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, sizeof(char) * 4)},
	{Texture::ETextureFormats::RGBA16, Texture::FTexFormatToGLType(GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT, sizeof(short) * 4)},
	{Texture::ETextureFormats::RGBA32, Texture::FTexFormatToGLType(GL_RGBA32F, GL_RGBA, GL_FLOAT, sizeof(float) * 4)},
	{Texture::ETextureFormats::RGB8, Texture::FTexFormatToGLType(GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, sizeof(char) * 3)},
	{Texture::ETextureFormats::RGB16, Texture::FTexFormatToGLType(GL_RGB16F, GL_RGB, GL_HALF_FLOAT, sizeof(short) * 3)},
	{Texture::ETextureFormats::RGB32, Texture::FTexFormatToGLType(GL_RGB32F, GL_RGB, GL_FLOAT, sizeof(float) * 3)},
	{Texture::ETextureFormats::RG8, Texture::FTexFormatToGLType(GL_RG8, GL_RG, GL_UNSIGNED_BYTE, sizeof(char) * 2)},
	{Texture::ETextureFormats::RG16, Texture::FTexFormatToGLType(GL_RG16F, GL_RG, GL_HALF_FLOAT, sizeof(short) * 2)},
	{Texture::ETextureFormats::RG32, Texture::FTexFormatToGLType(GL_RG32F, GL_RG, GL_FLOAT, sizeof(float) * 2)},
	{Texture::ETextureFormats::R8, Texture::FTexFormatToGLType(GL_R8, GL_RED, GL_UNSIGNED_BYTE, sizeof(char) * 1)},
	{Texture::ETextureFormats::R16, Texture::FTexFormatToGLType(GL_R16F, GL_RED, GL_HALF_FLOAT, sizeof(short) * 1)},
	{Texture::ETextureFormats::R32, Texture::FTexFormatToGLType(GL_R32F, GL_RED, GL_FLOAT, sizeof(float) * 1)},
	{Texture::ETextureFormats::Depth, Texture::FTexFormatToGLType(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, sizeof(float) * 1)},
};

Texture::FTextureData::FTextureData()
{
	m_Data = nullptr;
	m_Width = 0;
	m_Height = 0;
	m_Depth = 0;
	m_bGenerateMips = false;
	m_Format = ETextureFormats::RGBA8;
}

Texture::FTextureData::~FTextureData()
{
	delete[] m_Data;
}

void Texture::Begin()
{
	m_RenderData = new FTextureData();
	m_TextureID = 0;
	glGenTextures(1, &m_TextureID);
}

void Texture::End()
{
	delete m_RenderData;
	glDeleteTextures(1, &m_TextureID);
}

Texture::FTextureData* Texture::GetTextureData() const
{
	return m_RenderData;
}

unsigned int Texture::GetTextureID() const
{
	return m_TextureID;
}