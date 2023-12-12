#include "Core/Math.h"

bool Math::RayPlaneIntersection(const glm::vec3& InPlaneNormal, const glm::vec3& InPlaneLocation, const glm::vec3& InRayOrigin, const glm::vec3& InRayDirection, float& OutT)
{
	// assuming vectors are all normalized
	float Denom = glm::dot(InPlaneNormal, InRayDirection);
	
	if (Denom > 1e-6)
	{
		glm::vec3 p0l0 = InPlaneLocation - InRayOrigin;
		OutT = glm::dot(p0l0, InPlaneNormal) / Denom;
		return (OutT >= 0);
	}

	return false;
}
