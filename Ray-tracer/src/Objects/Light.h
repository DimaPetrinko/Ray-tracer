#pragma once
#include "Object.h"

class Light : public Object
{
public:
	float bias;
public:
	Light(const Vec3& position, float bias) : Object(position), bias(bias) {}
private:
	void Init() override {}
};