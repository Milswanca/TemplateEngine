#include "Rendering/Assets/Mesh.h"
#include "Rendering/RHI/RHI.h"
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

	MeshData* RenderData = NewMesh->GetRenderData();
	RenderData->SetPositions(Vertices);
	RenderData->SetUVs(UVs);
	RenderData->AddSection(Indices, nullptr);
	RenderData->Build();

	return NewMesh;
}

Mesh::MeshData::MeshData()
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

	m_VertexStateObject = nullptr;
	m_VertexBuffer = nullptr;
	m_IndexBuffer = nullptr;
}

Mesh::MeshData::~MeshData()
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

	RHIDeleteVertexStateObject(m_VertexStateObject);
	RHIDeleteBuffer(m_VertexBuffer);
	RHIDeleteBuffer(m_IndexBuffer);
}

void Mesh::MeshData::SetPositions(const std::vector<glm::vec3>& InPositions)
{
	delete[] m_Positions;
	m_Positions = new glm::vec3[InPositions.size()];
	memcpy(m_Positions, InPositions.data(), sizeof(glm::vec3) * InPositions.size());
	m_NumPositions = InPositions.size();
}

void Mesh::MeshData::SetNormals(const std::vector<glm::vec3>& InNormals)
{
	delete[] m_Normals;
	m_Normals = new glm::vec3[InNormals.size()];
	memcpy(m_Normals, InNormals.data(), sizeof(glm::vec3) * InNormals.size());
	m_NumNormals = InNormals.size();
}

void Mesh::MeshData::SetTangents(const std::vector<glm::vec3>& InTangents)
{
	delete[] m_Tangents;
	m_Tangents = new glm::vec3[InTangents.size()];
	memcpy(m_Tangents, InTangents.data(), sizeof(glm::vec3) * InTangents.size());
	m_NumTangents = InTangents.size();
}

void Mesh::MeshData::SetBitangents(const std::vector<glm::vec3>& InBitangents)
{
	delete[] m_Bitangents;
	m_Bitangents = new glm::vec3[InBitangents.size()];
	memcpy(m_Bitangents, InBitangents.data(), sizeof(glm::vec3) * InBitangents.size());
	m_NumBitangents = InBitangents.size();
}

void Mesh::MeshData::SetUVs(const std::vector<glm::vec2>& InUVs)
{
	delete[] m_UVs;
	m_UVs = new glm::vec2[InUVs.size()];
	memcpy(m_UVs, InUVs.data(), sizeof(glm::vec2) * InUVs.size());
	m_NumUVs = InUVs.size();
}

void Mesh::MeshData::SetColors(const std::vector<glm::vec4>& InColors)
{
	delete[] m_Colors;
	m_Colors = new glm::vec4[InColors.size()];
	memcpy(m_Colors, InColors.data(), sizeof(glm::vec4) * InColors.size());
	m_NumColors = InColors.size();
}

const unsigned int* Mesh::MeshData::GetIndices() const
{
	return m_Indices;
}

unsigned int Mesh::MeshData::AddSection(const std::vector<unsigned int>& InIndices, Material* InMaterial)
{
	unsigned int* NewIndices = new unsigned int[m_NumIndices + InIndices.size()];
	memcpy(NewIndices, m_Indices, sizeof(unsigned int) * m_NumIndices);
	memcpy((NewIndices + m_NumIndices), InIndices.data(), sizeof(unsigned int) * InIndices.size());

	delete[] m_Indices;
	m_Indices = NewIndices;

	MeshSection** NewSections = new MeshSection*[m_NumSections + 1];
	memcpy(NewSections, m_Sections, sizeof(MeshSection) * m_NumSections);

	MeshSection* NewMeshSection = new MeshSection();
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

void Mesh::MeshData::RemoveSection(unsigned int SectionIndex)
{
	MeshSection* Section = m_Sections[SectionIndex];
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
	MeshSection** NewSections = new MeshSection*[m_NumSections - 1];
	memcpy(NewSections, m_Sections, sizeof(MeshSection) * SectionIndex);
	memcpy((NewSections + SectionIndex), (m_Sections + SectionIndex + 1), sizeof(MeshSection) * (m_NumSections - (SectionIndex + 1)));

	delete[] m_Sections;
	m_Sections = NewSections;

	m_NumSections--;
}

void Mesh::MeshData::Build()
{
	RHIDeleteVertexStateObject(m_VertexStateObject);
	RHIDeleteBuffer(m_VertexBuffer);
	RHIDeleteBuffer(m_IndexBuffer);
	
	unsigned int PositionsBufferSizeBytes = (sizeof(glm::vec3) * m_NumPositions);
	unsigned int UVsBufferSizeBytes = (sizeof(glm::vec2) * m_NumUVs);
	unsigned int NormalsBufferSizeBytes = (sizeof(glm::vec3) * m_NumNormals);
	unsigned int TangentsBufferSizeBytes = (sizeof(glm::vec3) * m_NumTangents);
	unsigned int BitangentsBufferSizeBytes = (sizeof(glm::vec3) * m_NumBitangents);
	unsigned int ColorsBufferSizeBytes = (sizeof(glm::vec4) * m_NumColors);

	unsigned int VertexBufferSizeBytes =
		PositionsBufferSizeBytes + UVsBufferSizeBytes + NormalsBufferSizeBytes +
		TangentsBufferSizeBytes + BitangentsBufferSizeBytes + ColorsBufferSizeBytes;

	unsigned int PositionsOffsetBytes = 0;
	unsigned int UVsOffsetBytes = PositionsOffsetBytes + PositionsBufferSizeBytes;
	unsigned int NormalsOffsetBytes = UVsOffsetBytes + UVsBufferSizeBytes;
	unsigned int TangentsOffsetBytes = NormalsOffsetBytes + NormalsBufferSizeBytes;
	unsigned int BitangentsOffsetBytes = TangentsOffsetBytes + TangentsBufferSizeBytes;
	unsigned int ColorsOffsetBytes = BitangentsOffsetBytes + BitangentsBufferSizeBytes;

	// Vertex Buffer
	RHIBufferDesc VertexBufferDesc;
	VertexBufferDesc.m_Size = VertexBufferSizeBytes;
	VertexBufferDesc.m_Stride = 0;
	m_VertexBuffer = RHICreateVertexBuffer(VertexBufferDesc);
	RHIUpdateBufferData(m_VertexBuffer, PositionsBufferSizeBytes, PositionsOffsetBytes, m_Positions);
	RHIUpdateBufferData(m_VertexBuffer, UVsBufferSizeBytes, UVsOffsetBytes, m_UVs);
	RHIUpdateBufferData(m_VertexBuffer, NormalsBufferSizeBytes, NormalsOffsetBytes, m_Normals);
	RHIUpdateBufferData(m_VertexBuffer, TangentsBufferSizeBytes, TangentsOffsetBytes, m_Tangents);
	RHIUpdateBufferData(m_VertexBuffer, BitangentsBufferSizeBytes, BitangentsOffsetBytes, m_Bitangents);
	RHIUpdateBufferData(m_VertexBuffer, ColorsBufferSizeBytes, ColorsOffsetBytes, m_Colors);

	// Index Buffer
	RHIBufferDesc IndexBufferDesc;
	IndexBufferDesc.m_Size = m_NumIndices * sizeof(unsigned int);
	IndexBufferDesc.m_Stride = 0;
	m_IndexBuffer = RHICreateIndexBuffer(IndexBufferDesc);
	RHISetIndexBufferIndices(m_IndexBuffer, m_NumIndices, m_Indices);
	
	// Vertex Layout
	RHIVertexAttributeArray Attributes(6);
	Attributes.SetAttribute(0, RHIVertexAttributeDesc("Positions", VertexAttributeTypes::Float, 3, false, sizeof(glm::vec3), PositionsOffsetBytes));
	Attributes.SetAttribute(1, RHIVertexAttributeDesc("UVs", VertexAttributeTypes::Float, 2, false, sizeof(glm::vec2), UVsOffsetBytes));
	Attributes.SetAttribute(2, RHIVertexAttributeDesc("Normals", VertexAttributeTypes::Float, 3, true, sizeof(glm::vec3), NormalsOffsetBytes));
	Attributes.SetAttribute(3, RHIVertexAttributeDesc("Tangents", VertexAttributeTypes::Float, 3, true, sizeof(glm::vec3), TangentsOffsetBytes));
	Attributes.SetAttribute(4, RHIVertexAttributeDesc("Bitangents", VertexAttributeTypes::Float, 3, true, sizeof(glm::vec3), BitangentsOffsetBytes));
	Attributes.SetAttribute(5, RHIVertexAttributeDesc("Colors", VertexAttributeTypes::Float, 4, false, sizeof(glm::vec4), ColorsOffsetBytes));

	// Vertex State Object
	m_VertexStateObject = RHICreateVertexStateObject(m_VertexBuffer, m_IndexBuffer, Attributes);
}

unsigned int Mesh::MeshData::GetNumSections() const
{
	return m_NumSections;
}

const Mesh::MeshSection* Mesh::MeshData::GetMeshSection(unsigned int SectionIndex) const
{
	return m_Sections[SectionIndex];
}

RHIVertexStateObject* Mesh::MeshData::GetVertexStateObject() const
{
	return m_VertexStateObject;
}

RHIVertexBuffer* Mesh::MeshData::GetVertexBuffer() const
{
	return m_VertexBuffer;
}

RHIIndexBuffer* Mesh::MeshData::GetIndexBuffer() const
{
	return m_IndexBuffer;
}

void Mesh::Begin()
{
	m_RenderData = new MeshData();
}

void Mesh::End()
{
	delete m_RenderData;
}

Mesh::MeshData* Mesh::GetRenderData() const
{
	return m_RenderData;
}