#include "Color.h"

Color::Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a)
{
	c = a | b << 8 | g << 16 | r << 24;
}

uint8_t Color::r() const { return c >> 24; }
uint8_t Color::g() const { return c >> 16; }
uint8_t Color::b() const { return c >> 8; }
uint8_t Color::a() const { return c; }