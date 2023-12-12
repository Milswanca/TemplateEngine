#pragma once
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Transform
{
    Transform();
    ~Transform();
    
    void SetLocalPosition(const glm::vec3& InLocalPosition);
    void SetLocalRotation(const glm::quat& InLocalRotation);
    void SetLocalScale(const glm::vec3& InLocalScale);

    void TranslateLocal(const glm::vec3& InTranslation);
    void TranslateWorld(const glm::vec3& InTranslation);

    void Rotate(float InDegrees, const glm::vec3& InAxis);
    void Rotate(const glm::quat& InQuaternion);
    void Rotate(const glm::vec3& InEuler);

    glm::vec3 GetLocalPosition() const;
    glm::quat GetLocalRotation() const;
    glm::vec3 GetLocalScale() const;

    glm::vec3 GetPosition() const;
    glm::quat GetRotation() const;

    glm::vec3 GetForward() const;
    glm::vec3 GetRight() const;
    glm::vec3 GetUp() const;

    void GetLocalToWorld(glm::mat4& OutLocalToWorld) const;
    void GetWorldToLocal(glm::mat4& OutWorldToLocal) const;

    void SetParent(Transform* NewParent);
    Transform* GetParent() const;

private:
    void ApplyTransformation();
    void RecalculateSpaceTransforms();
    
    void AddChild(Transform* InNewChild);
    void RemoveChild(Transform* InRemChild);
    
    glm::mat4 m_LocalToWorld;
    glm::mat4 m_WorldToLocal;
    glm::mat4 m_RelativeTransform;

    glm::vec3 m_Position;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;

    Transform* m_Parent;
    std::vector<Transform*> m_Children;
};