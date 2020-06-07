#pragma once

#include <string>
#include "bmp.hpp"
#include "Math/Vec2.h"
#include "Tracing/Color.h"

class Texture
{
private:
	BMP bmp;
public:
	Texture(const std::string& path);
	Texture(const int& width, const int& height);

	Color GetPixel(const Vec2& uv) const;
	Color GetPixel(const int& u, const int& v) const;
	void SetPixel(const Vec2& uv, const Color& color);
	void SetPixel(const int& u, const int& v, const Color& color);
	void Save(const std::string& path);
};