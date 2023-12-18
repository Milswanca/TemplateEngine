#pragma once
#include "Rendering/Assets/Texture.h"
#include <string>

class RHITexture;

class Texture2D : public Texture
{
public:
	static Texture2D* Create(const std::string& InFile);
	static Texture2D* Create(unsigned int InWidth, unsigned int InHeight, ETextureFormats InFormat);

protected:
	IMPLEMENT_CONSTRUCTOR(Texture2D, Texture);
};