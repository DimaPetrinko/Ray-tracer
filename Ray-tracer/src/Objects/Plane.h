#pragma once

#include "Renderable.h"

class Plane : public Renderable 
{
public:
	Vec3 normal;

public:
	Plane(const Vec3& position, const Vec3& normal,
		const Color& color, const Color& specularColor);
	Hit Intersect(const Ray& ray)  const override;
};