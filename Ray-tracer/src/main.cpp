#include <iostream>
#include "bmp.hpp"

struct Color
{
    uint32_t c;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0xff)
    {
        c = a | b << 8 | g << 16 | r << 24;
    }

    uint8_t r() { return c >> 24; }
    uint8_t g() { return c >> 16; }
    uint8_t b() { return c >> 8; }
    uint8_t a() { return c; }
};

struct Vec3
{
    float x, y, z;
    Vec3 operator+(Vec3 other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(Vec3 other)
    {
        return {x - other.x, y - other.y, z - other.z};
    }
};

struct Vec2
{
    float x, y;

    Vec2 operator+(Vec2 other)
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(Vec2 other)
    {
        return {x - other.x, y - other.y};
    }
};

struct Ray
{
    Vec3 origin;
    Vec3 direction;
};

class Camera
{
public:
    Vec3 position = {0, 0, 0};
    Vec3 direction = {0, 0, -1};
    Vec3 up = {0, 1, 0};
};

class Renderable
{
    Vec3 position;
    virtual bool Interects(Ray ray) = 0;
};

int FlattenIndex(int x, int y, int width)
{
    return y * width + x;
}

const int screenWidth = 800;
const int screenHeight = 600;
const Vec2 clipPlanes = {1, 1000};

int main()
{
    Camera camera{position : {0, 0, 0}, direction : {0, 0, -1}};

    BMP bmp2(800, 600);
    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            Color c{0xff, 0xa0, 0x00};

            auto r = c.r();
            bmp2.set_pixel(x, y, c.b(), c.g(), c.r(), c.a());
        }
    }
    bmp2.write("Ray-tracer/res/img_test.bmp");
}