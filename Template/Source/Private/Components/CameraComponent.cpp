#include "Components/CameraComponent.h"
#include "Core/Engine.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

CameraComponent* CameraComponent::s_MainCamera = nullptr;

void CameraComponent::Begin()
{
	Component::Begin();

	m_bUseWindowAspect = true;
	m_ProjectionType = EProjectionTypes::Perspective;
	m_Near = 0.03f;
	m_Far = 1000.0f;
	m_FOV = 45.0f;
	m_Aspect = 1.0f;
	m_OrthoWidth = 300;
	RefreshProjectionView();
}

void CameraComponent::Tick(float InDelta)
{
	Component::Tick(InDelta);
	RefreshProjectionView();
}

void CameraComponent::End()
{
	Component::End();
}

void CameraComponent::SetAsMain()
{
	s_MainCamera = this;
}

CameraComponent* CameraComponent::GetMain()
{
	return s_MainCamera;
}

void CameraComponent::SetUseWindowAspect(bool bInUseWindowAspect)
{
	m_bUseWindowAspect = bInUseWindowAspect;
	RefreshProjectionView();
}

void CameraComponent::SetProjectionType(EProjectionTypes Type)
{
	m_ProjectionType = Type;
	RefreshProjectionView();
}

void CameraComponent::SetFOV(float NewFOV)
{
	m_FOV = NewFOV;
	RefreshProjectionView();
}

void CameraComponent::SetNear(float NewNear)
{
	m_Near = NewNear;
	RefreshProjectionView();
}

void CameraComponent::SetFar(float NewFar)
{
	m_Far = NewFar;
	RefreshProjectionView();
}

void CameraComponent::SetOrthoSize(float Width, float Height)
{
	m_OrthoWidth = Width;
	m_OrthoHeight = Height;
	RefreshProjectionView();
}

void CameraComponent::SetOrthoFitMode(EOrthoFitMode FitMode)
{
	m_OrthoFitMode = FitMode;
	RefreshProjectionView();
}

void CameraComponent::DeprojectScreenToWorld(const glm::vec3& Screen, glm::vec3& Location, glm::vec3& Direction)
{
	float HalfScreenWidth = Engine::s_WindowWidth * 0.5f;
	float HalfScreenHeight = Engine::s_WindowHeight * 0.5f;

	glm::mat4 InvMat = glm::inverse(m_ProjectionView);
	glm::vec4 Near = glm::vec4((Screen.x - HalfScreenWidth) / HalfScreenWidth, -1.0f * (Screen.y - HalfScreenHeight) / HalfScreenHeight, -1.0f, 1.0f);
	glm::vec4 Far = glm::vec4((Screen.x - HalfScreenWidth) / HalfScreenWidth, -1.0f * (Screen.y - HalfScreenHeight) / HalfScreenHeight, 1.0f, 1.0);
	glm::vec4 NearResult = InvMat * Near;
	glm::vec4 FarResult = InvMat * Far;
	NearResult /= NearResult.w;
	FarResult /= FarResult.w;

	Location = NearResult;
	Direction = glm::normalize(glm::vec3(FarResult - NearResult));
}

bool CameraComponent::GetUseWindowAspect() const
{
	return m_bUseWindowAspect;
}

EProjectionTypes CameraComponent::GetProjectionType() const
{
	return m_ProjectionType;
}

float CameraComponent::GetFOV() const
{
	return m_FOV;
}

float CameraComponent::GetNear() const
{
	return m_Near;
}

float CameraComponent::GetFar() const
{
	return m_Far;
}

glm::mat4 CameraComponent::GetProjection() const
{
	return m_Projection;
}

glm::mat4 CameraComponent::GetView() const
{
	return m_View;
}

glm::mat4 CameraComponent::GetProjectionView() const
{
	return m_ProjectionView;
}

void CameraComponent::RefreshProjectionView()
{
	float Aspect = (float)Engine::s_WindowWidth / (float)Engine::s_WindowHeight;

	if (m_ProjectionType == EProjectionTypes::Perspective)
	{
		m_Projection = glm::perspective(GetFOV(), Aspect, GetNear(), GetFar());
	}
	else
	{
		float OrthoAspect = m_OrthoWidth / m_OrthoHeight;
		float FinalWidth = 0.0f;
		float FinalHeight = 0.0f;

		switch (m_OrthoFitMode)
		{
		case EOrthoFitMode::Stretch:
			FinalWidth = m_OrthoWidth;
			FinalHeight = m_OrthoHeight;
			break;

		case EOrthoFitMode::FlexibleWidth:
			FinalWidth = m_OrthoHeight * Aspect;
			FinalHeight = m_OrthoHeight;
			break;

		case EOrthoFitMode::FlexibleHeight:
			FinalWidth = m_OrthoWidth;
			FinalHeight = m_OrthoWidth * (1.0f / Aspect);
			break;

		case EOrthoFitMode::Fit:
			if (Aspect < OrthoAspect)
			{
				FinalWidth = m_OrthoWidth;
				FinalHeight = m_OrthoWidth * (1.0f / Aspect);
			}
			else
			{
				FinalWidth = m_OrthoHeight * Aspect;
				FinalHeight = m_OrthoHeight;
			}
			break;
		}

		m_Projection = glm::ortho(-FinalWidth * 0.5f, FinalWidth * 0.5f, -FinalHeight * 0.5f, FinalHeight * 0.5f, GetNear(), GetFar());
	}

	glm::vec3 Forward = GetForward();
	glm::vec3 Position = GetPosition();
	glm::vec3 Up = GetUp();
	m_View = glm::lookAt(GetPosition(), GetPosition() + (GetForward() * 100.0f), GetUp());
	m_ProjectionView = m_Projection * m_View;
}