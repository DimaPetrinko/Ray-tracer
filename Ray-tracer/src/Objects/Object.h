#pragma once

#include "Math/Vec3.h"

class Object
{
public:
	Vec3 position = {0, 0, 0};
public:
	Object(const Vec3& position) : position(position) {}
private:
	virtual void Init() = 0;
};