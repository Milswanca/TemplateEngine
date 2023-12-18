#pragma once
#include "Core/Actor.h"
#include <glm/glm.hpp>
#include "glm/ext/quaternion_float.hpp"

class Actor;

struct ActorSpawnParams
{
	glm::vec3 m_Translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat m_Rotation = glm::identity<glm::quat>();
	glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class World : public Object
{
	IMPLEMENT_CONSTRUCTOR(World, Object);

public:
	virtual void Begin() override;
	void TickWorld(float InDelta);
	virtual World* GetWorld() const override;

	template<typename T>
	T* SpawnActor()
	{
		ActorSpawnParams Params;
		return SpawnActor<T>(Params);
	}

	template<typename T>
	T* SpawnActor(const ActorSpawnParams& InParams)
	{
		T* NewActor = s_Engine->NewObject<T>(this);
		NewActor->SetLocalPosition(InParams.m_Translation);
		NewActor->SetLocalRotation(InParams.m_Rotation);
		NewActor->SetLocalScale(InParams.m_Scale);
		m_Actors.push_back(NewActor);
		return NewActor;
	}

	void DestroyActor(Actor* InToDestroy)
	{
		m_Actors.erase(std::remove(m_Actors.begin(), m_Actors.end(), InToDestroy), m_Actors.end());
		s_Engine->DestroyObject(InToDestroy);
	}

private:
	std::vector<Actor*> m_Actors;
	World* m_ConstThis;
};

