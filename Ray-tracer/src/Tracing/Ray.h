#pragma once

#include "Math/Vec3.h"
#include "Color.h"

struct Ray
{
	Vec3 origin;
	Vec3 direction;
	Color energy;
	float lenght;
};
