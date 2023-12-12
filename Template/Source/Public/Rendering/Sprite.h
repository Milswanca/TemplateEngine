#pragma once
#include "Core/Object.h"
#include <string>
#include <glm/glm.hpp>

class Texture2D;

class Sprite : public Object
{
public:
	static Sprite* Create(const std::string& InFile);
	static Sprite* Create(unsigned int InWidth, unsigned int InHeight);

protected:
	IMPLEMENT_CONSTRUCTOR(Sprite, Object);

	virtual void Begin() override;

public:
	void OverrideDimensions(unsigned int InWidth, unsigned int InHeight);
	void GetDimensions(unsigned int& OutWidth, unsigned int& OutHeight) const;
	glm::mat4 GetScaleMatrix() const;

	Texture2D* GetTexture() const;

private:
	bool m_bOverrideDimensions;
	unsigned int m_OverrideWidth;
	unsigned int m_OverrideHeight;

	Texture2D* m_Texture;
};