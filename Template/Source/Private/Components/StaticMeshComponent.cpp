#include "Components/StaticMeshComponent.h"

#include "Rendering/Assets/Mesh.h"
#include "Rendering/RHI/RHI.h"

void StaticMeshComponent::Tick(float InDelta)
{
    Component::Tick(InDelta);

    Mesh::MeshData* MeshData = m_Mesh->GetRenderData();
    RHIBindVertexStateObject(MeshData->GetVertexStateObject()); 
    
    for(int i = 0; i < MeshData->GetNumSections(); ++i)
    {
        const Mesh::MeshSection* MeshSection = MeshData->GetMeshSection(i);
        RHIDrawElements(MeshSection->m_NumIndices, MeshSection->m_IndexOffset);
    }
}

void StaticMeshComponent::SetMesh(Mesh* InMesh)
{
    m_Mesh = InMesh;
}

Mesh* StaticMeshComponent::GetMesh() const
{
    return m_Mesh;
}