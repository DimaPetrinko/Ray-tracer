#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Vec3& position, const float& radius, const Color& color)
	: Renderable(position, color), radius(radius) {}

Hit Sphere::Intersect(const Ray& ray) const
{
	Hit hit = Hit();
	hit.distance = ray.lenght;
	hit.position = ray.origin + ray.direction * hit.distance;

	Vec3 directionToCenter = ray.origin - position;
	float p1 = -Dot(ray.direction, directionToCenter);
	float p2sqr = p1 * p1 - Dot(directionToCenter, directionToCenter) + radius * radius;
	if (p2sqr < 0) return hit;

	float p2 = std::sqrt(p2sqr);
	hit.distance = p1 - p2 > 0 ? p1 - p2 : p1 + p2;
	hit.position = ray.origin + ray.direction * hit.distance;
	hit.normal = (hit.position - position).Normalized();
	// hit.color = color;
	Vec3 colorNormal = hit.normal / 2 + Vec3{0.5f ,0.5f, 0.5f};
	hit.color = {colorNormal.x * 255, colorNormal.y * 255, colorNormal.z * 255, 255};

	return hit;
}
