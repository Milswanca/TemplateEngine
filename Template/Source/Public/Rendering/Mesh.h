#pragma once
#include "Core/Object.h"
#include "glm/glm.hpp"
#include <vector>

class Material;

class Mesh : public Object
{
public:
	struct FMeshSection
	{
		Material* m_Mat;
		unsigned int m_IndexOffset;
		unsigned int m_NumIndices;
	};

	struct FMeshData
	{
	public:
		void SetPositions(const std::vector<glm::vec3>& InPositions);
		void SetNormals(const std::vector<glm::vec3>& InNormals);
		void SetTangents(const std::vector<glm::vec3>& InTangents);
		void SetBitangents(const std::vector<glm::vec3>& InBitangents);
		void SetUVs(const std::vector<glm::vec2>& InUVs);
		void SetColors(const std::vector<glm::vec4>& InColors);

		const unsigned int* GetIndices() const;

		unsigned int AddSection(const std::vector<unsigned int>& InIndices, Material* InMaterial);
		void RemoveSection(unsigned int InSectionIndex);
		unsigned int GetNumSections() const;
		const FMeshSection* GetMeshSection(unsigned int InSectionIndex) const;

	private:
		FMeshData();
		~FMeshData();

		glm::vec3* m_Positions;
		glm::vec3* m_Normals;
		glm::vec3* m_Tangents;
		glm::vec3* m_Bitangents;
		glm::vec2* m_UVs;
		glm::vec4* m_Colors;
		unsigned int* m_Indices;
		FMeshSection** m_Sections;

		unsigned int m_NumPositions;
		unsigned int m_NumUVs;
		unsigned int m_NumNormals;
		unsigned int m_NumTangents;
		unsigned int m_NumBitangents;
		unsigned int m_NumColors;
		unsigned int m_NumIndices;
		unsigned int m_NumSections;

		friend class Mesh;
	};

public:
	static Mesh* CreateQuad();

protected:
	IMPLEMENT_CONSTRUCTOR(Mesh, Object);

public:
	virtual void Begin() override;
	virtual void End() override;

	void Build();
	FMeshData* GetRenderData() const;

	unsigned int GetVAO() const;

private:
	unsigned int m_VertexBuffer;
	unsigned int m_IndexBuffer;
	unsigned int m_VertexArrayObject;

	unsigned int m_PositionsBufferSizeBytes;
	unsigned int m_UVsBufferSizeBytes;
	unsigned int m_NormalsBufferSizeBytes;
	unsigned int m_TangentsBufferSizeBytes;
	unsigned int m_BitangentsBufferSizeBytes;
	unsigned int m_ColorsBufferSizeBytes;
	unsigned int m_VertexBufferSizeBytes;

	unsigned int m_PositionsOffsetBytes;
	unsigned int m_UVsOffsetBytes;
	unsigned int m_NormalsOffsetBytes;
	unsigned int m_TangentsOffsetBytes;
	unsigned int m_BitangentsOffsetBytes;
	unsigned int m_ColorsOffsetBytes;

	FMeshData* m_RenderData;
};

