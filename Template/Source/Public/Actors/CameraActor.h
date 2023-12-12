#pragma once
#include "Core/Actor.h"
#include "Components/CameraComponent.h"

class CameraActor : public Actor
{
protected:
	IMPLEMENT_CONSTRUCTOR(CameraActor, Actor);

	virtual void Begin() override;

public:
	inline CameraComponent* GetCameraComponent() const { return m_CameraComponent; }

private:
	CameraComponent* m_CameraComponent;
};

