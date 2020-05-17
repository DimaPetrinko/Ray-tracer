#include "Vec2.h"
#include <cmath>

float Vec2::Magnitude() const
{
	return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const
{
	float m = Magnitude();
	return {x / m, y / m};
}

float Vec2::Dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

float Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return {x - other.x, y - other.y};
}

Vec2 Vec2::operator*(const float& scale) const
{
	return {x * scale, y * scale};
}

Vec2 Vec2::operator/(const float& scale) const
{
	return {x / scale, y / scale};
}