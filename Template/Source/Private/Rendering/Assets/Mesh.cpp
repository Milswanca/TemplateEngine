#include "Rendering/Assets/Mesh.h"
#include "Core/Engine.h"
#include <glad/glad.h>

Mesh* Mesh::CreateQuad()
{
	Mesh* NewMesh = Engine::Get()->NewObject<Mesh>();

	std::vector<glm::vec3> Vertices = {
		glm::vec3(-0.5, -0.5, 0.0), // bottom left corner
		glm::vec3(-0.5, 0.5, 0.0), // top left corner
		glm::vec3(0.5, 0.5, 0.0), // top right corner
		glm::vec3(0.5, -0.5, 0.0) // bottom right corner
	};

	std::vector<glm::vec2> UVs = {
		glm::vec2(0, 1), // bottom left corner
		glm::vec2(0, 0), // top left corner
		glm::vec2(1, 0), // top right corner
		glm::vec2(1, 1) // bottom right corner
	};

	std::vector<unsigned int> Indices = {
		0,1,2, // first triangle (bottom left - top left - top right)
		0,2,3 // second triangle (bottom left - top right - bottom right)
	};

	FMeshData* RenderData = NewMesh->GetRenderData();
	RenderData->SetPositions(Vertices);
	RenderData->SetUVs(UVs);
	RenderData->AddSection(Indices, nullptr);
	NewMesh->Build();

	return NewMesh;
}

Mesh::FMeshData::FMeshData()
{
	m_Positions = nullptr;
	m_Normals = nullptr;
	m_Tangents = nullptr;
	m_Bitangents = nullptr;
	m_UVs = nullptr;
	m_Colors = nullptr;
	m_Indices = nullptr;
	m_Sections = nullptr;
	
	m_NumPositions = 0;
	m_NumUVs = 0;
	m_NumNormals = 0;
	m_NumTangents = 0;
	m_NumBitangents = 0;
	m_NumColors = 0;
	m_NumIndices = 0;
	m_NumSections = 0;
}

Mesh::FMeshData::~FMeshData()
{
	for (int i = 0; i < m_NumSections; ++i)
	{
		delete m_Sections[i];
	}

	delete[] m_Positions;
	delete[] m_Normals;
	delete[] m_Tangents;
	delete[] m_Bitangents;
	delete[] m_UVs;
	delete[] m_Colors;
	delete[] m_Indices;
	delete[] m_Sections;

	m_NumPositions = 0;
	m_NumUVs = 0;
	m_NumNormals = 0;
	m_NumTangents = 0;
	m_NumBitangents = 0;
	m_NumColors = 0;
	m_NumIndices = 0;
	m_NumSections = 0;
}

void Mesh::FMeshData::SetPositions(const std::vector<glm::vec3>& InPositions)
{
	delete[] m_Positions;
	m_Positions = new glm::vec3[InPositions.size()];
	memcpy(m_Positions, InPositions.data(), sizeof(glm::vec3) * InPositions.size());
	m_NumPositions = InPositions.size();
}

void Mesh::FMeshData::SetNormals(const std::vector<glm::vec3>& InNormals)
{
	delete[] m_Normals;
	m_Normals = new glm::vec3[InNormals.size()];
	memcpy(m_Normals, InNormals.data(), sizeof(glm::vec3) * InNormals.size());
	m_NumNormals = InNormals.size();
}

void Mesh::FMeshData::SetTangents(const std::vector<glm::vec3>& InTangents)
{
	delete[] m_Tangents;
	m_Tangents = new glm::vec3[InTangents.size()];
	memcpy(m_Tangents, InTangents.data(), sizeof(glm::vec3) * InTangents.size());
	m_NumTangents = InTangents.size();
}

void Mesh::FMeshData::SetBitangents(const std::vector<glm::vec3>& InBitangents)
{
	delete[] m_Bitangents;
	m_Bitangents = new glm::vec3[InBitangents.size()];
	memcpy(m_Bitangents, InBitangents.data(), sizeof(glm::vec3) * InBitangents.size());
	m_NumBitangents = InBitangents.size();
}

void Mesh::FMeshData::SetUVs(const std::vector<glm::vec2>& InUVs)
{
	delete[] m_UVs;
	m_UVs = new glm::vec2[InUVs.size()];
	memcpy(m_UVs, InUVs.data(), sizeof(glm::vec2) * InUVs.size());
	m_NumUVs = InUVs.size();
}

void Mesh::FMeshData::SetColors(const std::vector<glm::vec4>& InColors)
{
	delete[] m_Colors;
	m_Colors = new glm::vec4[InColors.size()];
	memcpy(m_Colors, InColors.data(), sizeof(glm::vec4) * InColors.size());
	m_NumUVs = InColors.size();
}

const unsigned int* Mesh::FMeshData::GetIndices() const
{
	return m_Indices;
}

unsigned int Mesh::FMeshData::AddSection(const std::vector<unsigned int>& InIndices, Material* InMaterial)
{
	unsigned int* NewIndices = new unsigned int[m_NumIndices + InIndices.size()];
	memcpy(NewIndices, m_Indices, sizeof(unsigned int) * m_NumIndices);
	memcpy((NewIndices + m_NumIndices), InIndices.data(), sizeof(unsigned int) * InIndices.size());

	delete[] m_Indices;
	m_Indices = NewIndices;

	FMeshSection** NewSections = new FMeshSection*[m_NumSections + 1];
	memcpy(NewSections, m_Sections, sizeof(FMeshSection) * m_NumSections);

	FMeshSection* NewMeshSection = new FMeshSection();
	NewMeshSection->m_Mat = InMaterial;
	NewMeshSection->m_IndexOffset = m_NumIndices;
	NewMeshSection->m_NumIndices = InIndices.size();
	NewSections[m_NumSections] = NewMeshSection;

	delete[] m_Sections;
	m_Sections = NewSections;

	m_NumIndices += InIndices.size();
	m_NumSections += 1;

	return m_NumSections - 1;
}

void Mesh::FMeshData::RemoveSection(unsigned int SectionIndex)
{
	FMeshSection* Section = m_Sections[SectionIndex];
	unsigned int StartIndex = Section->m_IndexOffset;
	unsigned int EndIndices = Section->m_IndexOffset + Section->m_NumIndices;
	unsigned int SectionNumIndices = Section->m_NumIndices;
	unsigned int NewNumIndices = m_NumIndices - SectionNumIndices;

	// Remove the Indices by not copying it
	unsigned int* NewIndices = new unsigned int[NewNumIndices];
	memcpy(NewIndices, m_Indices, sizeof(unsigned int) * StartIndex);
	memcpy((NewIndices + StartIndex), (m_Indices + EndIndices), sizeof(unsigned int) * (m_NumIndices - EndIndices));
	m_NumIndices = NewNumIndices;

	delete[] m_Indices;
	m_Indices = NewIndices;

	for (unsigned int i = SectionIndex; i < m_NumSections - 1; ++i)
	{
		m_Sections[i]->m_IndexOffset -= SectionNumIndices;
	}

	// Remove the mesh section by not copying it
	FMeshSection** NewSections = new FMeshSection*[m_NumSections - 1];
	memcpy(NewSections, m_Sections, sizeof(FMeshSection) * SectionIndex);
	memcpy((NewSections + SectionIndex), (m_Sections + SectionIndex + 1), sizeof(FMeshSection) * (m_NumSections - (SectionIndex + 1)));

	delete[] m_Sections;
	m_Sections = NewSections;

	m_NumSections--;
}

unsigned int Mesh::FMeshData::GetNumSections() const
{
	return m_NumSections;
}

const Mesh::FMeshSection* Mesh::FMeshData::GetMeshSection(unsigned int SectionIndex) const
{
	return m_Sections[SectionIndex];
}

void Mesh::Begin()
{
	glGenBuffers(1, &m_IndexBuffer);
	glGenBuffers(1, &m_VertexBuffer);
	glGenVertexArrays(1, &m_VertexArrayObject);

	m_RenderData = new FMeshData();

	m_PositionsBufferSizeBytes = 0;
	m_UVsBufferSizeBytes = 0;
	m_NormalsBufferSizeBytes = 0;
	m_TangentsBufferSizeBytes = 0;
	m_BitangentsBufferSizeBytes = 0;
	m_ColorsBufferSizeBytes = 0;
	m_VertexBufferSizeBytes = 0;

	m_PositionsOffsetBytes = 0;
	m_UVsOffsetBytes = 0;
	m_NormalsOffsetBytes = 0;
	m_TangentsOffsetBytes = 0;
	m_BitangentsOffsetBytes = 0;
	m_ColorsOffsetBytes = 0;
}

void Mesh::End()
{
	glDeleteBuffers(1, &m_IndexBuffer);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteVertexArrays(1, &m_VertexArrayObject);

	delete m_RenderData;
}

void Mesh::Build()
{
	m_PositionsBufferSizeBytes = (sizeof(glm::vec3) * m_RenderData->m_NumPositions);
	m_UVsBufferSizeBytes = (sizeof(glm::vec2) * m_RenderData->m_NumUVs);
	m_NormalsBufferSizeBytes = (sizeof(glm::vec3) * m_RenderData->m_NumNormals);
	m_TangentsBufferSizeBytes = (sizeof(glm::vec3) * m_RenderData->m_NumTangents);
	m_BitangentsBufferSizeBytes = (sizeof(glm::vec3) * m_RenderData->m_NumBitangents);
	m_ColorsBufferSizeBytes = (sizeof(glm::vec4) * m_RenderData->m_NumColors);

	m_VertexBufferSizeBytes =
		m_PositionsBufferSizeBytes + m_UVsBufferSizeBytes + m_NormalsBufferSizeBytes +
		m_TangentsBufferSizeBytes + m_BitangentsBufferSizeBytes + m_ColorsBufferSizeBytes;

	m_PositionsOffsetBytes = 0;
	m_UVsOffsetBytes = m_PositionsOffsetBytes + m_PositionsBufferSizeBytes;
	m_NormalsOffsetBytes = m_UVsOffsetBytes + m_UVsBufferSizeBytes;
	m_TangentsOffsetBytes = m_NormalsOffsetBytes + m_NormalsBufferSizeBytes;
	m_BitangentsOffsetBytes = m_TangentsOffsetBytes + m_TangentsBufferSizeBytes;
	m_ColorsOffsetBytes = m_BitangentsOffsetBytes + m_BitangentsBufferSizeBytes;

	glBindVertexArray(m_VertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_VertexBufferSizeBytes, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, m_PositionsOffsetBytes, m_PositionsBufferSizeBytes, m_RenderData->m_Positions);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)m_PositionsOffsetBytes);

	glBufferSubData(GL_ARRAY_BUFFER, m_UVsOffsetBytes, m_UVsBufferSizeBytes, m_RenderData->m_UVs);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)m_UVsOffsetBytes);

	glBufferSubData(GL_ARRAY_BUFFER, m_NormalsOffsetBytes, m_NormalsBufferSizeBytes, m_RenderData->m_Normals);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)m_NormalsOffsetBytes);

	glBufferSubData(GL_ARRAY_BUFFER, m_TangentsOffsetBytes, m_TangentsBufferSizeBytes, m_RenderData->m_Tangents);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)m_TangentsOffsetBytes);

	glBufferSubData(GL_ARRAY_BUFFER, m_BitangentsOffsetBytes, m_BitangentsBufferSizeBytes, m_RenderData->m_Bitangents);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_TRUE, 0, (GLvoid*)m_BitangentsOffsetBytes);

	glBufferSubData(GL_ARRAY_BUFFER, m_ColorsOffsetBytes, m_ColorsBufferSizeBytes, m_RenderData->m_Colors);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)m_ColorsOffsetBytes);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_RenderData->m_NumIndices * sizeof(unsigned int), m_RenderData->m_Indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::FMeshData* Mesh::GetRenderData() const
{
	return m_RenderData;
}

unsigned int Mesh::GetVAO() const
{
	return m_VertexArrayObject;
}
