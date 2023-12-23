#pragma once
#include "Core/Actor.h"
#include "Components/StaticMeshComponent.h"

class StaticMeshActor : public Actor
{
protected:
    IMPLEMENT_CONSTRUCTOR(StaticMeshActor, Actor);

    virtual void Begin() override;

public:
    inline StaticMeshComponent* GetStaticMeshComponent() const { return m_StaticMeshComponent; }

private:
    StaticMeshComponent* m_StaticMeshComponent;
};
