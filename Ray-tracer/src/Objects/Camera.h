#pragma once

#include "Object.h"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Tracing/Ray.h"

class Camera : public Object
{
public:
	Vec3 direction = {0, 0, -1};
	Vec3 up = {0, 1, 0};
	float zoom;

public:
	Camera(const Vec3& position, const Vec3& direction, const float& zoom, const Vec3& up = {0, 1, 0});
	Vec3 ZoomedDirection() const;
	Ray CreateRay(const Vec3& uv, const Vec2& clipPlanes) const;
private:
	void Init() override {};
};