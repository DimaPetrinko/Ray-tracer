#pragma once
#include "Object.h"

class Light : public Object
{
public:
	float intensity;
	float bias;
public:
	Light(const Vec3& position, const float& intensity, const float& bias)
		: Object(position), intensity(intensity), bias(bias) {}
private:
	void Init() override {}
};