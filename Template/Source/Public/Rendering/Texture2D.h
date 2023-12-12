#pragma once
#include "Rendering/Texture.h"
#include <string>

class Texture2D : public Texture
{
public:
	static Texture2D* Create(const std::string& InFile);
	static Texture2D* Create(unsigned int InWidth, unsigned int InHeight, ETextureFormats InFormat);

protected:
	IMPLEMENT_CONSTRUCTOR(Texture2D, Texture);

public:
	virtual void Build() override;
};