#include "Rendering/Sprite.h"
#include "Rendering/Texture2D.h"
#include "Core/Engine.h"

#include <glm/ext/matrix_transform.hpp>

Sprite* Sprite::Create(const std::string& InFile)
{
	Sprite* NewSprite = Engine::Get()->NewObject<Sprite>();
	NewSprite->m_Texture = Texture2D::Create(InFile);
	return NewSprite;
}

Sprite* Sprite::Create(unsigned int InWidth, unsigned int InHeight)
{
	Sprite* NewSprite = Engine::Get()->NewObject<Sprite>();
	NewSprite->m_Texture = Texture2D::Create(InWidth, InHeight, RHITexture::ETextureFormats::RGBA8);
	return NewSprite;
}

void Sprite::Begin()
{
	Object::Begin();

	m_OverrideWidth = 0;
	m_OverrideHeight = 0;
	m_bOverrideDimensions = false;
	m_Texture = nullptr;
}

void Sprite::OverrideDimensions(unsigned int InWidth, unsigned int InHeight)
{
	m_OverrideWidth = InWidth;
	m_OverrideHeight = InHeight;
	m_bOverrideDimensions = true;
}

void Sprite::GetDimensions(unsigned int& OutWidth, unsigned int& OutHeight) const
{
	if (m_bOverrideDimensions)
	{
		OutWidth = m_OverrideWidth;
		OutHeight = m_OverrideHeight;
	}
	else
	{
		OutWidth = m_Texture->GetTextureData()->m_Width;
		OutHeight = m_Texture->GetTextureData()->m_Height;
	}
}

glm::mat4 Sprite::GetScaleMatrix() const
{
	unsigned int Width;
	unsigned int Height;
	GetDimensions(Width, Height);
	return glm::scale(glm::identity<glm::mat4>(), glm::vec3(Width, Height, 1.0f));
}

Texture2D* Sprite::GetTexture() const
{
	return m_Texture;
}