#pragma once
#include <glm/glm.hpp>

class Sprite;
class Material;

class IRendererImmediate
{
public:
	void DrawSprite(Sprite* InSprite, Material* InMaterial, const glm::mat4& InTransform)
	{
		DrawSprite(InSprite, InMaterial, glm::vec4(1.0f), InTransform);
	}

	virtual void DrawSprite(Sprite* InSprite, Material* InMaterial, const glm::vec4& InTint, const glm::mat4& InTransform) = 0;
};

