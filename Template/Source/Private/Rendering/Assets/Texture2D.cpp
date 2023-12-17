#include "Rendering/Resources/Texture2D.h"

#if RENDERER_OPENGL

#include "Core/Engine.h"
#include "Utils/FileUtils.h"
#include "SOIL/SOIL.h"

Texture2D* Texture2D::Create(const std::string& InFile)
{
	Texture2D* NewTexture = Engine::Get()->NewObject<Texture2D>();

	FTextureData* Data = NewTexture->GetTextureData();
	Data->m_bGenerateMips = false;

	int NumChannels;
	Data->m_Data = SOIL_load_image(InFile.c_str(), &Data->m_Width, &Data->m_Height, &NumChannels, SOIL_LOAD_AUTO);

	switch (NumChannels)
	{
	case 1:
		Data->m_Format = ETextureFormats::R8;
		break;
	case 2:
		Data->m_Format = ETextureFormats::RG8;
		break;
	case 3:
		Data->m_Format = ETextureFormats::RGB8;
		break;
	case 4:
		Data->m_Format = ETextureFormats::RGBA8;
		break;
	}

	NewTexture->Build();
	return NewTexture;
}

Texture2D* Texture2D::Create(unsigned int InWidth, unsigned int InHeight, ETextureFormats InFormat)
{
	Texture2D* NewTexture = Engine::Get()->NewObject<Texture2D>();

	FTextureData* Data = NewTexture->GetTextureData();
	Data->m_bGenerateMips = false;
	Data->m_Width = InWidth;
	Data->m_Height = InHeight;
	Data->m_Format = InFormat;
	Data->m_Data = new unsigned char[InWidth * InHeight * 4];
	memset(Data->m_Data, 255, InWidth * InHeight * 4);

	NewTexture->Build();

	return NewTexture;
}

void Texture2D::Build()
{
	FTextureData* TextureData = GetTextureData();
	
	FTexFormatToGLType GLData = s_TexFormatsToGLTypes[TextureData->m_Format];
	glBindTexture(GL_TEXTURE_2D, GetTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GLData.m_SourceFormat, TextureData->m_Width, TextureData->m_Height, 0, GLData.m_DesiredFormat, GLData.m_DataType, TextureData->m_Data);

	if (TextureData->m_bGenerateMips)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}

#endif