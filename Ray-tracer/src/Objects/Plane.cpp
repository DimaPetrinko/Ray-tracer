#include "Plane.h"

Plane::Plane(const Vec3& position, const Vec3& normal, const Color& color, const Color& specularColor)
	: Renderable(position, color, specularColor), normal(normal) {}

Hit Plane::Intersect(const Ray& ray) const
{
	Hit hit = Hit();
	hit.distance = ray.lenght;
	hit.position = ray.origin + ray.direction * hit.distance;

	float rayDirectionNormalDot = Dot(ray.direction, normal);
	if (rayDirectionNormalDot == 0) return hit;
	Vec3 directionToPlane = position - ray.origin;
	float directionToPlaneNormalDot = Dot(directionToPlane, normal);
	float distance = directionToPlaneNormalDot / rayDirectionNormalDot;

	if (distance > ray.lenght) return hit; 

	hit.distance = distance;
	hit.position = ray.origin + ray.direction * hit.distance;
	hit.normal = normal;
	hit.object = (Renderable*)this;

	return hit;
}
