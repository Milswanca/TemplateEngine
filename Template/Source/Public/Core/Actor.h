#pragma once
#include "Core/Object.h"
#include "Core/Component.h"
#include "Core/Engine.h"
#include <vector>

#include "glm/ext/quaternion_float.hpp"

class Component;

class Actor : public Object
{
protected:
	IMPLEMENT_CONSTRUCTOR(Actor, Object);

protected:
	virtual void Begin() override;
	virtual void Tick(float InDelta);
	virtual void End() override;

public:
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

	template<typename T>
	T* AddComponent()
	{
		T* NewComp = s_Engine->NewObject<T>(this);
		m_Components.push_back(NewComp);

		return NewComp;
	}

	void DestroyComponent(Component* InComp, bool InRemoveChildren);
	void DestroyActor();

	Component* GetRootComponent() const;

private:
	void DestroyComponentTree(Component* InComp);

	Component* m_RootComponent;
	std::vector<Component*> m_Components;

	friend class World;
};