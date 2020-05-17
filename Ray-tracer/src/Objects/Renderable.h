#pragma once

#include "Object.h"
#include "Tracing/Hit.h"
#include "Tracing/Ray.h"

class Renderable : public Object
{
public:
	Color color;
public:
	Renderable(const Vec3& position, const Color& color) : Object(position), color(color) {}
	virtual Hit Intersect(const Ray& ray) const = 0;
private:
	void Init() override {};
};