#include "Actors/CameraActor.h"

void CameraActor::Begin()
{
	Actor::Begin();

	m_CameraComponent = AddComponent<CameraComponent>();
	m_CameraComponent->AttachTo(GetRootComponent());
}