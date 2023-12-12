#include "Rendering/RendererImmediateGL.h"
#include "Rendering/Sprite.h"
#include "Rendering/Material.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture2D.h"
#include "Components/CameraComponent.h"
#include "Utils/FileUtils.h"

#include <glm/ext/matrix_transform.hpp>

Mesh* RendererImmediateGL::m_QuadMesh = nullptr;
Shader* RendererImmediateGL::m_SpriteDefaultShader = nullptr;
Material* RendererImmediateGL::m_SpriteDefaultMaterial = nullptr;

void RendererImmediateGL::Begin()
{
	Object::Begin();

	if (m_QuadMesh == nullptr)
		m_QuadMesh = Mesh::CreateQuad();

	if (m_SpriteDefaultShader == nullptr)
	{
		Shader::FCreateShaderParams Params;
		Params.m_VertexShader = FileUtils::GetContentDirectory() + "Engine/Shaders/SpriteVertex.shader";
		Params.m_FragmentShader = FileUtils::GetContentDirectory() + "Engine/Shaders/SpriteFragment.shader";
		m_SpriteDefaultShader = Shader::Create(Params);
	}

	if (m_SpriteDefaultMaterial == nullptr)
		m_SpriteDefaultMaterial = Material::Create(m_SpriteDefaultShader);
}

void RendererImmediateGL::End()
{
	Object::End();
}

void RendererImmediateGL::DrawSprite(Sprite* InSprite, Material* InMaterial, const glm::vec4& InTint, const glm::mat4& InTransform)
{
	if (InSprite != nullptr)
	{
		glm::mat4 PixelScale = InSprite->GetScaleMatrix();

		Mesh::FMeshData* RenderData = m_QuadMesh->GetRenderData();
		int NumSections = RenderData->GetNumSections();

		glBindVertexArray(m_QuadMesh->GetVAO());
		for (int i = 0; i < NumSections; ++i)
		{
			glm::mat4 ProjectionView = CameraComponent::GetMain() != nullptr ? CameraComponent::GetMain()->GetProjectionView() : glm::identity<glm::mat4>();

			Material* Mat = InMaterial == nullptr ? m_SpriteDefaultMaterial : InMaterial;
			Mat->SetMat4("gProjectionView", ProjectionView);
			Mat->SetMat4("gModel", InTransform * PixelScale);
			Mat->SetVector4("gTint", InTint);
			Mat->SetTexture("gSprite", InSprite != nullptr ? InSprite->GetTexture() : nullptr);
			Mat->Bind();

			const Mesh::FMeshSection* Section = RenderData->GetMeshSection(i);
			glDrawElements(GL_TRIANGLES, Section->m_NumIndices, GL_UNSIGNED_INT, reinterpret_cast<void*>(Section->m_IndexOffset));

			Mat->Unbind();
		}
		glBindVertexArray(0);
	}
}