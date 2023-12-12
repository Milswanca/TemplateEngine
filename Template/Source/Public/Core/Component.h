#pragma once
#include "Core/Object.h"
#include <vector>

#include "glm/glm.hpp"
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

struct Transform;

class Component : public Object
{
protected:
	IMPLEMENT_CONSTRUCTOR(Component, Object);

protected:
	virtual void Begin() override;
	virtual void Tick(float InDelta);
	virtual void End() override;

public:
	void AttachTo(Component* Other);

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

	Component* GetParent() const;
	Component* GetChild(int InIndex) const;
	int GetNumChildren() const;

private:
	void TickComponentTree(float InDelta);

	void AddChild(Component* InChild);
	void RemoveChild(Component* InChild);

	std::vector<Component*> m_Children;

	Component* m_ParentComponent;
	Transform* m_Trans;

	friend class Actor;
};