#include <iostream>

struct Pixel
{
    float r, g, b;
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

Pixel image[screenWidth * screenHeight] = {};

int main()
{
    Camera camera{position : {0, 0, 0}, direction : {0, 0, -1}};

    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            image[FlattenIndex(x, y, screenWidth)] = {1, 1, 1};
        }
    }
}