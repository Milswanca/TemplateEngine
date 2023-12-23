#include "Rendering/Assets/Texture.h"
#include "Rendering/RHI/RHI.h"

void Texture::Begin()
{
	Object::Begin();

	m_RHITexture = nullptr;
}

void Texture::End()
{
	Object::End();

	RHIDeleteTexture(m_RHITexture);
}

void Texture::CreateInternalTexture(const CreateTextureDesc& InDesc, unsigned char* InRawMemory)
{
	RHIDeleteTexture(m_RHITexture);
	m_RHITexture = RHICreateTexture(InDesc);
	RHISetTexturePixels(m_RHITexture, InRawMemory);
}

const RHITexture* Texture::GetInternalTexture() const
{
	return m_RHITexture;
}
