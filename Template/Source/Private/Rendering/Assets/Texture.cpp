#include "Rendering/Assets/Texture.h"
#include "Rendering/RHI/RHI.h"

void Texture::CreateInternalTexture(const CreateTextureDesc& InDesc, unsigned char* InRawMemory)
{
	if (m_RHITexture)
	{
		RHIDeleteTexture(m_RHITexture);
	}

	m_RHITexture = RHICreateTexture(InDesc);
	RHISetTexturePixels(m_RHITexture, InRawMemory);
}

const RHITexture* Texture::GetInternalTexture() const
{
	return m_RHITexture;
}
