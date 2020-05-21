#include "Color.h"

Color::Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a)
{
	c = a | b << 8 | g << 16 | r << 24;
}

uint8_t Color::r() const { return c >> 24; }
uint8_t Color::g() const { return c >> 16; }
uint8_t Color::b() const { return c >> 8; }
uint8_t Color::a() const { return c; }

void Color::r(const uint8_t& r)
{
	c = a() | b() << 8 | g() << 16 | r << 24;
}

void Color::g(const uint8_t& g)
{
	c = a() | b() << 8 | g << 16 | r() << 24;
}

void Color::b(const uint8_t& b)
{
	c = a() | b << 8 | g() << 16 | r() << 24;
}

void Color::a(const uint8_t& a)
{
	c = a | b() << 8 | g() << 16 | r() << 24;
}

Color Color::operator+(const Color& other) const
{
	return Color(r() + other.r(), g() + other.g(), b() + other.b(), a() + other.a());
}

Color Color::operator-(const Color& other) const
{
	return Color(r() - other.r(), g() - other.g(), b() - other.b(), a() - other.a());
}

Color Color::operator*(const float& scale) const
{
	return Color(r() * scale, g() * scale, b() * scale, a() * scale);
}

Color Color::operator/(const float& fraction) const
{
	return Color(r() / fraction, g() / fraction, b() / fraction, a() / fraction);
}