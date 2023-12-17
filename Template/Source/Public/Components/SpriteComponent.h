#pragma once
#include "Core/Component.h"

class Mesh;
class Sprite;
class RHIShaderProgram;
class Material;

class SpriteComponent : public Component
{
protected:
	IMPLEMENT_CONSTRUCTOR(SpriteComponent, Component);

	virtual void Begin() override;
	virtual void Tick(float InDelta) override;
	virtual void End() override;

public:
	void SetSprite(Sprite* InSprite);
	Sprite* GetSprite() const;

	void SetMaterial(Material* InMaterial);
	Material* GetMaterial() const;

private:
	Sprite* m_Sprite;
	Material* m_Material;
};