#pragma once
#include "Object.h"

class Light : public Object
{
public:
	Light(const Vec3& position) : Object(position) {}
private:
	void Init() override {}
};