#pragma once
#include "Core/Object.h"
#include "Rendering/RHI/Resources/RHITexture.h"
#include <string>

class RHITexture;

class Texture : public Object
{
protected:
	IMPLEMENT_CONSTRUCTOR(Texture, Object);

	virtual void Begin() override;
	virtual void End() override;

	void CreateInternalTexture(const CreateTextureDesc& InDesc, unsigned char* InRawMemory);
	const RHITexture* GetInternalTexture() const;

private:
	RHITexture* m_RHITexture = nullptr;
};