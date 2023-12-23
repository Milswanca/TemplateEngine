#include "Actors/StaticMeshActor.h"

void StaticMeshActor::Begin()
{
    Actor::Begin();

    m_StaticMeshComponent = AddComponent<StaticMeshComponent>();
    m_StaticMeshComponent->AttachTo(GetRootComponent());
}