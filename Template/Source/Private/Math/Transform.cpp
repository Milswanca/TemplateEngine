#include "Math/Transform.h"
#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
{
    m_Position = glm::vec3(0.0f, 0.0f, .0f);
    m_Rotation = glm::identity<glm::quat>();
    m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_RelativeTransform = glm::identity<glm::mat4>();
    m_LocalToWorld = glm::identity<glm::mat4>();
    m_WorldToLocal = glm::identity<glm::mat4>();

    m_Parent = nullptr;
}

Transform::~Transform()
{

}

void Transform::SetLocalPosition(const glm::vec3& InLocalPosition)
{
    m_Position = InLocalPosition;
    ApplyTransformation();
}

void Transform::SetLocalRotation(const glm::quat& InLocalRotation)
{
    m_Rotation = InLocalRotation;
    ApplyTransformation();
}

void Transform::SetLocalScale(const glm::vec3& InLocalScale)
{
    m_Scale = InLocalScale;
    ApplyTransformation();
}

void Transform::TranslateLocal(const glm::vec3& InTranslation)
{
	m_Position += GetRotation() * InTranslation;
	ApplyTransformation();
}

void Transform::TranslateWorld(const glm::vec3& InTranslation)
{
	m_Position += InTranslation;
    ApplyTransformation();
}

void Transform::Rotate(float InDegrees, const glm::vec3& InAxis)
{
    m_Rotation = glm::angleAxis(glm::radians(InDegrees), InAxis) * m_Rotation;
    ApplyTransformation();
}

void Transform::Rotate(const glm::quat& InQuaternion)
{
	m_Rotation = InQuaternion * m_Rotation;
	ApplyTransformation();
}

void Transform::Rotate(const glm::vec3& InEuler)
{
	m_Rotation = glm::quat(glm::vec3(glm::radians(InEuler.x), glm::radians(InEuler.y), glm::radians(InEuler.z))) * m_Rotation;
	ApplyTransformation();
}

glm::vec3 Transform::GetLocalPosition() const
{
    return m_Position;
}

glm::quat Transform::GetLocalRotation() const
{
    return m_Rotation;
}

glm::vec3 Transform::GetLocalScale() const
{
    return m_Scale;
}

glm::vec3 Transform::GetPosition() const
{
    return m_LocalToWorld * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

glm::quat Transform::GetRotation() const
{
    return glm::toQuat(m_LocalToWorld);
}

glm::vec3 Transform::GetForward() const
{
    return m_LocalToWorld * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
}

glm::vec3 Transform::GetRight() const
{
    return m_LocalToWorld * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
}

glm::vec3 Transform::GetUp() const
{
    return m_LocalToWorld * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
}

void Transform::GetLocalToWorld(glm::mat4& OutLocalToWorld) const
{
    OutLocalToWorld = m_LocalToWorld;
}

void Transform::GetWorldToLocal(glm::mat4& OutWorldToLocal) const
{
    OutWorldToLocal = m_WorldToLocal;
}

void Transform::SetParent(Transform* InParent)
{
    if(m_Parent != nullptr)
    {
        m_Parent->RemoveChild(this);
    }

    m_Parent = InParent;

    if(m_Parent)
    {
        m_Parent->AddChild(this);
    }

    ApplyTransformation();
}

Transform* Transform::GetParent() const
{
    return m_Parent;
}

void Transform::ApplyTransformation()
{
    //Calc Matrices here
    glm::mat4 T = glm::translate(glm::identity<glm::mat4>(), m_Position);
    glm::mat4 R = glm::toMat4(m_Rotation);
    glm::mat4 S = glm::scale(glm::identity<glm::mat4>(), m_Scale);

    m_RelativeTransform = T * R * S;
    RecalculateSpaceTransforms();
}

void Transform::RecalculateSpaceTransforms()
{
    m_LocalToWorld = m_Parent != nullptr ? m_Parent->m_LocalToWorld * m_RelativeTransform : m_RelativeTransform;
    m_WorldToLocal = glm::inverse(m_LocalToWorld);
    
    for(size_t i = 0; i < m_Children.size(); ++i)
    {
        m_Children[i]->ApplyTransformation();
    }
}

void Transform::AddChild(Transform* InNewChild)
{
    m_Children.push_back(InNewChild);
}

void Transform::RemoveChild(Transform* InRemChild)
{
    remove(m_Children.begin(), m_Children.end(), InRemChild);
}