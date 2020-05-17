#pragma once

#include "Math/Vec3.h"
#include "Color.h"

struct Hit
{
	Vec3 position;
	Vec3 normal;
	float distance;
	Color color;
};
