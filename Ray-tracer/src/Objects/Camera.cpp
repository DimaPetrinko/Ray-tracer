#include "Camera.h"

Camera::Camera(const Vec3& position, const Vec3& direction, const float& zoom, const Vec3& up)
	: Object(position), direction(direction), zoom(zoom), up(up) {}

Vec3 Camera::ZoomedDirection() const
{
	return direction.Normalized() * zoom;
}

Ray Camera::CreateRay(const Vec3& uv, const Vec2& clipPlanes) const
{
	return Ray {origin : position, direction : (ZoomedDirection() + uv).Normalized(), lenght: clipPlanes.y};
}