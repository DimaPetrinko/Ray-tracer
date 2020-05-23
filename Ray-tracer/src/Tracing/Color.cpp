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
	uint16_t r16 = r() + other.r();	if (r16 > 255) r16 = 255;
	uint16_t g16 = g() + other.g();	if (g16 > 255) g16 = 255;
	uint16_t b16 = b() + other.b();	if (b16 > 255) b16 = 255;
	uint16_t a16 = a() + other.a();	if (a16 > 255) a16 = 255;
	return Color(r16, g16, b16, a16);
}

Color Color::operator-(const Color& other) const
{
	uint8_t r8 = other.r() < r() ? r() - other.r() : 0;
	uint8_t g8 = other.g() < g() ? g() - other.g() : 0;
	uint8_t b8 = other.b() < b() ? b() - other.b() : 0;
	uint8_t a8 = other.a() < a() ? a() - other.a() : 0;
	return Color(r8, g8, b8, a8);
}

Color Color::operator*(const Color& other) const
{
	uint16_t r16 = r() * other.r();
	uint16_t g16 = g() * other.g();
	uint16_t b16 = b() * other.b();
	uint16_t a16 = a() * other.a();
	return Color(r16 / 255, g16 / 255, b16 / 255, a16 / 255);
}

Color Color::operator*(const float& scale) const
{
	uint32_t r32 = r() * scale;	if (r32 > 255) r32 = 255;
	uint32_t g32 = g() * scale;	if (g32 > 255) g32 = 255;
	uint32_t b32 = b() * scale;	if (b32 > 255) b32 = 255;
	uint32_t a32 = a() * scale;	if (a32 > 255) a32 = 255;
	return Color(r32, g32, b32, a32);
}

Color Color::operator/(const float& fraction) const
{
	uint32_t r32 = r() / fraction;	if (r32 > 255) r32 = 255;
	uint32_t g32 = g() / fraction;	if (g32 > 255) g32 = 255;
	uint32_t b32 = b() / fraction;	if (b32 > 255) b32 = 255;
	uint32_t a32 = a() / fraction;	if (a32 > 255) a32 = 255;
	return Color(r32, g32, b32, a32);
}