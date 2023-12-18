#include "Rendering/Assets/Texture2D.h"
#include "Core/Engine.h"
#include "Utils/FileUtils.h"
#include "SOIL/SOIL.h"

Texture2D* Texture2D::Create(const std::string& InFile)
{
	Texture2D* NewTexture = Engine::Get()->NewObject<Texture2D>();

	int Width;
	int Height;
	int NumChannels;
	unsigned char* Data = SOIL_load_image(InFile.c_str(), &Width, &Height, &NumChannels, SOIL_LOAD_AUTO);

	ETextureFormats Format;
	switch (NumChannels)
	{
	case 1:
		Format = ETextureFormats::R8;
		break;
	case 2:
		Format = ETextureFormats::RG8;
		break;
	case 3:
		Format = ETextureFormats::RGB8;
		break;
	case 4:
		Format = ETextureFormats::RGBA8;
		break;
	}

	CreateTextureDesc Desc;
	Desc.CreateTexture2D(Width, Height, Format);
	NewTexture->CreateInternalTexture(Desc, Data);

	SOIL_free_image_data(Data);

	return NewTexture;
}

Texture2D* Texture2D::Create(unsigned int InWidth, unsigned int InHeight, ETextureFormats InFormat)
{
	Texture2D* NewTexture = Engine::Get()->NewObject<Texture2D>();

	CreateTextureDesc Desc;
	Desc.CreateTexture2D(InWidth, InHeight, InFormat);
	NewTexture->CreateInternalTexture(Desc, nullptr);

	return NewTexture;
}