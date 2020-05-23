#pragma once

struct Vec3
{
	float x, y, z;

	float Magnitude() const;
	Vec3 Normalized() const;
	float Dot(const Vec3& other) const;
	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const float& scale) const;
	Vec3 operator/(const float& scale) const;
};

float Dot (const Vec3& a, const Vec3& b);
Vec3 Reflect(const Vec3& v, const Vec3& n);