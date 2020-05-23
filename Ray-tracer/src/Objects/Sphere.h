#pragma once

#include "Renderable.h"

class Sphere : public Renderable 
{
public:
	float radius;

public:
	Sphere(const Vec3& position, const float& radius,
		const Color& color, const Color& specularColor);
	Hit Intersect(const Ray& ray)  const override;
};