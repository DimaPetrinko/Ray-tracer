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

	Color GetPixel(const Vec2& uv) const;
	void SetPixel(const Vec2& uv, const Color& color);
};