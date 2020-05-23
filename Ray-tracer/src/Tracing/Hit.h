#pragma once

#include "Math/Vec3.h"
#include "Color.h"

class Renderable;

struct Hit
{
	Vec3 position;
	Vec3 normal;
	float distance;
	Renderable* object;
};
