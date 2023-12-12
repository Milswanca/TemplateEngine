#pragma once
#include "Core/Component.h"

enum class EProjectionTypes
{
	Orthographic,
	Perspective
};

enum class EOrthoFitMode
{
	Stretch,
	Fit,
	FlexibleWidth,
	FlexibleHeight
};

class CameraComponent : public Component
{
protected:
	IMPLEMENT_CONSTRUCTOR(CameraComponent, Component);

	virtual void Begin() override;
	virtual void Tick(float InDelta) override;
	virtual void End() override;

public:
	void SetAsMain();
	static CameraComponent* GetMain();

	void SetUseWindowAspect(bool InUseWindowAspect);
	void SetProjectionType(EProjectionTypes InType);
	void SetFOV(float InFOV);
	void SetNear(float InNear);
	void SetFar(float InFar);
	void SetOrthoSize(float InWidth, float InHeight);
	void SetOrthoFitMode(EOrthoFitMode InMode);
	void DeprojectScreenToWorld(const glm::vec3& InScreen, glm::vec3& InLocation, glm::vec3& InDirection);

	bool GetUseWindowAspect() const;
	EProjectionTypes GetProjectionType() const;
	float GetFOV() const;
	float GetNear() const;
	float GetFar() const;

	glm::mat4 GetProjection() const;
	glm::mat4 GetView() const;
	glm::mat4 GetProjectionView() const;

private:
	void RefreshProjectionView();

	bool m_bUseWindowAspect;
	EProjectionTypes m_ProjectionType;
	float m_FOV;
	float m_Near;
	float m_Far;
	float m_Aspect;
	float m_OrthoHeight;
	float m_OrthoWidth;
	EOrthoFitMode m_OrthoFitMode;

	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::mat4 m_ProjectionView;

	static CameraComponent* s_MainCamera;
};

