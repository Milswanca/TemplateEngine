#include "Core/Component.h"
#include "Math/Transform.h"

void Component::Begin()
{
	m_Trans = new Transform();
	m_ParentComponent = nullptr;
}

void Component::Tick(float InDelta)
{

}

void Component::End()
{
	delete m_Trans;
	m_Trans = nullptr;
}

void Component::TickComponentTree(float InDelta)
{
	Tick(InDelta);

	for (int i = 0; i < m_Children.size(); ++i)
	{
		m_Children[i]->TickComponentTree(InDelta);
	}
}

void Component::AttachTo(Component* InOther)
{
	if (m_ParentComponent == InOther)
		return;

	if (m_ParentComponent != nullptr)
	{
		m_ParentComponent->RemoveChild(this);
	}

	Transform* ParentTrans = InOther != nullptr ? InOther->m_Trans : nullptr;
	m_Trans->SetParent(ParentTrans);

	if (InOther)
	{
		InOther->AddChild(this);
	}
}

void Component::AddChild(Component* InChild)
{
	if (std::find(m_Children.begin(), m_Children.end(), InChild) != m_Children.end())
		return;

	m_Children.push_back(InChild);
}

void Component::RemoveChild(Component* InChild)
{
	m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), InChild), m_Children.end());
}

void Component::SetLocalPosition(const glm::vec3& InLocalPosition)
{
	m_Trans->SetLocalPosition(InLocalPosition);
}

void Component::SetLocalRotation(const glm::quat& InLocalRotation)
{
	m_Trans->SetLocalRotation(InLocalRotation);
}

void Component::SetLocalScale(const glm::vec3& InLocalScale)
{
	m_Trans->SetLocalScale(InLocalScale);
}

void Component::TranslateLocal(const glm::vec3& InTranslation)
{
	m_Trans->TranslateLocal(InTranslation);
}

void Component::TranslateWorld(const glm::vec3& InTranslation)
{
	m_Trans->TranslateWorld(InTranslation);
}

void Component::Rotate(float InDegrees, const glm::vec3& InAxis)
{
	m_Trans->Rotate(InDegrees, InAxis);
}

void Component::Rotate(const glm::quat& InQuaternion)
{
	m_Trans->Rotate(InQuaternion);
}

void Component::Rotate(const glm::vec3& InEuler)
{
	m_Trans->Rotate(InEuler);
}

glm::vec3 Component::GetLocalPosition() const
{
	return m_Trans->GetLocalPosition();
}

glm::quat Component::GetLocalRotation() const
{
	return m_Trans->GetLocalRotation();
}

glm::vec3 Component::GetLocalScale() const
{
	return m_Trans->GetLocalScale();
}

glm::vec3 Component::GetPosition() const
{
	return m_Trans->GetPosition();
}

glm::quat Component::GetRotation() const
{
	return m_Trans->GetRotation();
}

glm::vec3 Component::GetForward() const
{
	return m_Trans->GetForward();
}

glm::vec3 Component::GetRight() const
{
	return m_Trans->GetRight();
}

glm::vec3 Component::GetUp() const
{
	return m_Trans->GetUp();
}

void Component::GetLocalToWorld(glm::mat4& OutLocalToWorld) const
{
	m_Trans->GetLocalToWorld(OutLocalToWorld);
}

void Component::GetWorldToLocal(glm::mat4& OutWorldToLocal) const
{
	m_Trans->GetWorldToLocal(OutWorldToLocal);
}

Component* Component::GetParent() const
{
	return m_ParentComponent;
}

Component* Component::GetChild(int InIndex) const
{
	return m_Children[InIndex];
}

int Component::GetNumChildren() const
{
	return m_Children.size();
}