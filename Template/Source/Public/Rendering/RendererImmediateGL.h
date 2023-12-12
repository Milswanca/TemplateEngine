#pragma once
#include "Core/Object.h"
#include "Rendering/IRendererImmediate.h"

class Mesh;
class Shader;
class Material;

class RendererImmediateGL : public Object, public IRendererImmediate
{
protected:
	IMPLEMENT_CONSTRUCTOR(RendererImmediateGL, Object);

	virtual void Begin() override;
	virtual void End() override;

public:
	virtual void DrawSprite(Sprite* InSprite, Material* InMaterial, const glm::vec4& InTint, const glm::mat4& InTransform) override;

private:
	static Mesh* m_QuadMesh;
	static Shader* m_SpriteDefaultShader;
	static Material* m_SpriteDefaultMaterial;
};

