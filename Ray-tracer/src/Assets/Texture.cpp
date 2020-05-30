#include "Texture.h"

Texture::Texture(const std::string& path) : bmp(path.c_str()) {}

Color Texture::GetPixel(const Vec2& uv) const
{
	uint8_t r, g, b, a;
	uint32_t x, y;

	x = uv.x * bmp.bmp_info_header.width;
	if (uv.x < 0) x = bmp.bmp_info_header.width + x;

	y = uv.y * bmp.bmp_info_header.height;
	if (uv.y < 0) y = bmp.bmp_info_header.height + y;

	bmp.get_pixel(x, y, b, g, r, a);
	if (a == 0) a = 0xff;
	return Color(r, g, b, a);
}

void Texture::SetPixel(const Vec2& uv, const Color& color)
{
	bmp.set_pixel(uv.x, uv.y, color.b(), color.g(), color.r(), color.a());
}