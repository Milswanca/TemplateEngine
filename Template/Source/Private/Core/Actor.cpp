#include "Core/Actor.h"
#include "Core/Engine.h"
#include "Core/World.h"

void Actor::Begin()
{
	m_RootComponent = AddComponent<Component>();
}

void Actor::Tick(float InDelta)
{
	m_RootComponent->TickComponentTree(InDelta);
}

void Actor::End()
{
	DestroyComponentTree(m_RootComponent);
}

void Actor::SetLocalPosition(const glm::vec3& InLocalPosition)
{
	m_RootComponent->SetLocalPosition(InLocalPosition);
}

void Actor::SetLocalRotation(const glm::quat& InLocalRotation)
{
	m_RootComponent->SetLocalRotation(InLocalRotation);
}

void Actor::SetLocalScale(const glm::vec3& InLocalScale)
{
	m_RootComponent->SetLocalScale(InLocalScale);
}

void Actor::TranslateLocal(const glm::vec3& InTranslation)
{
	m_RootComponent->TranslateLocal(InTranslation);
}

void Actor::TranslateWorld(const glm::vec3& InTranslation)
{
	m_RootComponent->TranslateWorld(InTranslation);
}

void Actor::Rotate(float InDegrees, const glm::vec3& InAxis)
{
	m_RootComponent->Rotate(InDegrees, InAxis);
}

void Actor::Rotate(const glm::quat& InQuaternion)
{
	m_RootComponent->Rotate(InQuaternion);
}

void Actor::Rotate(const glm::vec3& InEuler)
{
	m_RootComponent->Rotate(InEuler);
}

glm::vec3 Actor::GetLocalPosition() const
{
	return m_RootComponent->GetLocalPosition();
}

glm::quat Actor::GetLocalRotation() const
{
	return m_RootComponent->GetLocalRotation();
}

glm::vec3 Actor::GetLocalScale() const
{
	return m_RootComponent->GetLocalScale();
}

glm::vec3 Actor::GetPosition() const
{
	return m_RootComponent->GetPosition();
}

glm::quat Actor::GetRotation() const
{
	return m_RootComponent->GetRotation();
}

glm::vec3 Actor::GetForward() const
{
	return m_RootComponent->GetForward();
}

glm::vec3 Actor::GetRight() const
{
	return m_RootComponent->GetRight();
}

glm::vec3 Actor::GetUp() const
{
	return m_RootComponent->GetUp();
}

void Actor::GetLocalToWorld(glm::mat4& OutLocalToWorld) const
{
	m_RootComponent->GetLocalToWorld(OutLocalToWorld);
}

void Actor::GetWorldToLocal(glm::mat4& OutWorldToLocal) const
{
	m_RootComponent->GetWorldToLocal(OutWorldToLocal);
}

void Actor::DestroyActor()
{
	GetWorld()->DestroyActor(this);
}

void Actor::DestroyComponent(Component* InComp, bool InRemoveChildren)
{
	if (InComp == m_RootComponent)
		return;

	if (InRemoveChildren)
	{
		DestroyComponentTree(InComp);
	}
	else
	{
		Component* Parent = InComp->GetParent();
		int NumChildren = InComp->GetNumChildren();

		for (int i = 0; i < NumChildren; ++i)
		{
			Component* Child = InComp->GetChild(i);
			Child->AttachTo(Parent);
		}

		Engine::Get()->DestroyObject(InComp);
	}
}

void Actor::DestroyComponentTree(Component* InComp)
{
	int NumChildren = InComp->GetNumChildren();

	for (int i = 0; i < NumChildren; ++i)
	{
		DestroyComponentTree(InComp->GetChild(i));
	}

	Engine::Get()->DestroyObject(InComp);
}

Component* Actor::GetRootComponent() const
{
	return m_RootComponent;
}