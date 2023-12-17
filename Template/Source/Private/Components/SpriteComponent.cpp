#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "Core/Engine.h"
#include "Rendering/Sprite.h"
#include "Rendering/IRHI.h"

void SpriteComponent::Begin()
{
	Component::Begin();

	m_Sprite = nullptr;
}

void SpriteComponent::Tick(float InDelta)
{
	Component::Tick(InDelta);

	if (m_Sprite != nullptr)
	{
		glm::mat4 Model;
		GetLocalToWorld(Model);

		GetImmediateRenderer()->DrawSprite(m_Sprite, m_Material, Model);
	}
}

void SpriteComponent::End()
{
	Component::End();
}

void SpriteComponent::SetSprite(Sprite* InSprite)
{
	m_Sprite = InSprite;
}

Sprite* SpriteComponent::GetSprite() const
{
	return m_Sprite;
}

void SpriteComponent::SetMaterial(Material* InMaterial)
{
	m_Material = InMaterial;
}

Material* SpriteComponent::GetMaterial() const
{
	return m_Material;
}