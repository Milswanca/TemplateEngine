#pragma once
#include "Core/Object.h"
#include <glm/glm.hpp>

class Math : public Object
{
protected:
	IMPLEMENT_CONSTRUCTOR(Math, Object);

public:
	static bool RayPlaneIntersection(const glm::vec3& InPlaneNormal, const glm::vec3& InPlaneLocation, const glm::vec3& InRayOrigin, const glm::vec3& InRayDirection, float& OutT);
};

