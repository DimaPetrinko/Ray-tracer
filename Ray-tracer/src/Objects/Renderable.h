#pragma once

#include "Object.h"
#include "Tracing/Hit.h"
#include "Tracing/Ray.h"

class Renderable : public Object
{
public:
	Color color;
	Color specularColor;
public:
	Renderable(const Vec3& position, const Color& color, const Color& specularColor)
		: Object(position), color(color), specularColor(specularColor) {}
	virtual Hit Intersect(const Ray& ray) const = 0;
private:
	void Init() override {};
};