#include "Vec3.h"
#include <cmath>

float Vec3::Magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalized() const
{
	float m = Magnitude();
	return {x / m, y / m, z / m};
}

float Vec3::Dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Reflect(const Vec3& v, const Vec3& n)
{
	return v - n * 2 * Dot(v, n);
}

Vec3 Vec3::operator+(const Vec3& other) const
{
	return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3& other) const
{
	return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(const float& scale) const
{
	return {x * scale, y * scale, z * scale};
}

Vec3 Vec3::operator/(const float& scale) const
{
	return {x / scale, y / scale, z / scale};
}