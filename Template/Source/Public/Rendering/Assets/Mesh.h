#pragma once
#include "Core/Object.h"
#include "Rendering/RHI/Resources/RHIBuffer.h"
#include "Rendering/RHI/Resources/RHIVertexStateObject.h"
#include "glm/glm.hpp"
#include <vector>

class Material;

class Mesh : public Object
{
public:
	struct MeshSection
	{
		Material* m_Mat;
		unsigned int m_IndexOffset;
		unsigned int m_NumIndices;
	};

	struct MeshData
	{
	public:
		void SetPositions(const std::vector<glm::vec3>& InPositions);
		void SetNormals(const std::vector<glm::vec3>& InNormals);
		void SetTangents(const std::vector<glm::vec3>& InTangents);
		void SetBitangents(const std::vector<glm::vec3>& InBitangents);
		void SetUVs(const std::vector<glm::vec2>& InUVs);
		void SetColors(const std::vector<glm::vec4>& InColors);
		void Build();

		const unsigned int* GetIndices() const;

		unsigned int AddSection(const std::vector<unsigned int>& InIndices, Material* InMaterial);
		void RemoveSection(unsigned int InSectionIndex);
		unsigned int GetNumSections() const;
		const MeshSection* GetMeshSection(unsigned int InSectionIndex) const;

		RHIVertexStateObject* GetVertexStateObject() const;
		RHIVertexBuffer* GetVertexBuffer() const;
		RHIIndexBuffer* GetIndexBuffer() const;

	private:
		MeshData();
		~MeshData();

		glm::vec3* m_Positions;
		glm::vec3* m_Normals;
		glm::vec3* m_Tangents;
		glm::vec3* m_Bitangents;
		glm::vec2* m_UVs;
		glm::vec4* m_Colors;
		unsigned int* m_Indices;
		MeshSection** m_Sections;

		unsigned int m_NumPositions;
		unsigned int m_NumUVs;
		unsigned int m_NumNormals;
		unsigned int m_NumTangents;
		unsigned int m_NumBitangents;
		unsigned int m_NumColors;
		unsigned int m_NumIndices;
		unsigned int m_NumSections;

		RHIVertexBuffer* m_VertexBuffer;
		RHIIndexBuffer* m_IndexBuffer;
		RHIVertexStateObject* m_VertexStateObject;

		friend class Mesh;
	};

public:
	static Mesh* CreateQuad();

protected:
	IMPLEMENT_CONSTRUCTOR(Mesh, Object);

public:
	virtual void Begin() override;
	virtual void End() override;
	
	MeshData* GetRenderData() const;

private:	
	MeshData* m_RenderData;
};