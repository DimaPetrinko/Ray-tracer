#pragma once

struct Vec2
{
	float x, y;

	float Magnitude() const;
	Vec2 Normalized() const;
	float Dot(const Vec2& other) const;
	Vec2 operator+(const Vec2& other) const;
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator*(const float& scale) const;
	Vec2 operator/(const float& scale) const;
};

float Dot (const Vec2& a, const Vec2& b);