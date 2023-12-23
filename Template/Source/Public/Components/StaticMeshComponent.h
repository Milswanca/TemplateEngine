#pragma once
#include "Core/Component.h"

class Mesh;

class StaticMeshComponent : public Component
{
protected:
    IMPLEMENT_CONSTRUCTOR(StaticMeshComponent, Component);
    
public:    
    void Tick(float InDelta) override;
    
    void SetMesh(Mesh* InMesh);
    Mesh* GetMesh() const;
    
private:
    Mesh* m_Mesh;
};
