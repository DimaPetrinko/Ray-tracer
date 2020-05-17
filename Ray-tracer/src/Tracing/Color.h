#pragma once

#include <iostream>

struct Color
{
	uint32_t c;

	Color(const uint8_t& r = 0x00, const uint8_t& g = 0x00, const uint8_t& b = 0x00, const uint8_t& a = 0xff);

	uint8_t r() const;
	uint8_t g() const;
	uint8_t b() const;
	uint8_t a() const;
};