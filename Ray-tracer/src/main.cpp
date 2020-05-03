#include <iostream>
#include <cmath>
#include "bmp.hpp"

struct Color
{
    uint32_t c;

    Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0xff)
    {
        c = a | b << 8 | g << 16 | r << 24;
    }

    uint8_t r() const { return c >> 24; }
    uint8_t g() const { return c >> 16; }
    uint8_t b() const { return c >> 8; }
    uint8_t a() const { return c; }
};

struct Vec3
{
    float x, y, z;

    float Magnitude() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 Normalized() const
    {
        float m = Magnitude();
        return {x / m, y / m, z / m};
    }

    Vec3 operator+(Vec3 other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vec3 operator-(Vec3 other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 operator*(float scale) const
    {
        return {x * scale, y * scale, z * scale};
    }

    Vec3 operator/(float scale) const
    {
        return {x / scale, y / scale, z / scale};
    }
};

struct Vec2
{
    float x, y;

    Vec2 operator+(Vec2 other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(Vec2 other) const
    {
        return {x - other.x, y - other.y};
    }

    Vec2 operator*(float scale) const
    {
        return {x * scale, y * scale};
    }

    Vec2 operator/(float scale) const
    {
        return {x / scale, y / scale};
    }
};

float Dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Dot(Vec2 a, Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

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
    float zoom;

    Vec3 ZoomedDirection() const
    {
        return direction.Normalized() * zoom;
    }
};

class PointLight
{
public:
    Vec3 position = {0, 0, 0};
};

class Renderable
{
public:
    Vec3 position;

    Renderable(Vec3 position) : position(position) {}
    virtual float GetDistance(Vec3 point) const = 0;
};

class Sphere : public Renderable
{
public:
    float radius;

    Sphere(Vec3 position, float radius) : Renderable(position), radius(radius) {}

    virtual float GetDistance(Vec3 point) const override
    {
        return (point - position).Magnitude() - radius;
    }
};

class Plane : public Renderable
{
public:
    Plane(Vec3 position) : Renderable(position) {}

    virtual float GetDistance(Vec3 point) const override
    {
        return point.y - position.y;
    }
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const Vec2 CLIP_PLANES = {1, 2000};
const int MAX_STEPS = 100;
const float MIN_DISTANCE = 0.01f;
const float AMBIENT_LIGHT = 0.0f;
const float SHADOW_BIAS = 0.5f;

std::vector<Renderable *> renderables;
Camera *camera;
PointLight *light;

int FlattenIndex(int x, int y, int width)
{
    return y * width + x;
}

float GetMinDistance(Vec3 point)
{
    float minDistance = CLIP_PLANES.y;
    for (auto r : renderables)
    {
        float d = r->GetDistance(point);
        if (d < minDistance)
            minDistance = d;
    }
    return minDistance;
}

float March(const Ray &ray)
{
    float distance = 0;
    Vec3 rO = ray.origin;
    Vec3 rD = ray.direction;
    for (int i = 0; i < MAX_STEPS; i++)
    {
        Vec3 currentOrigin = rO + rD * distance;
        float currentDistance = GetMinDistance(currentOrigin);
        distance += currentDistance;
        if (currentDistance < MIN_DISTANCE || distance > CLIP_PLANES.y)
            break;
    }
    return distance;
}

Vec3 GetNormal(const Vec3 &point)
{
    float depth = GetMinDistance(point);
    float e = 0.01;

    Vec3 depthVec = {depth, depth, depth};
    Vec3 normal = depthVec - Vec3{GetMinDistance(point - Vec3{e, 0, 0}),
                                  GetMinDistance(point - Vec3{0, e, 0}),
                                  GetMinDistance(point - Vec3{0, 0, e})};
    return normal.Normalized();
}

float GetDiffuseColor(const Vec3 &point)
{
    Vec3 directionToLight = (light->position - point);
    Vec3 directionToLightNormalized = directionToLight.Normalized();
    Vec3 surfaceNormal = GetNormal(point);
    float diffuse = Dot(surfaceNormal, directionToLightNormalized);

    float distanceToLight = March({point + surfaceNormal, directionToLightNormalized});
    if (distanceToLight < directionToLight.Magnitude())
        diffuse *= 0.2f;
    return diffuse;
}

int main()
{
    camera = new Camera{position : {0, 25, -300}, direction : {0, 0, 1}, up : {}, zoom : 700};
    light = new PointLight{{500, 300, -350}};

    renderables.push_back(new Sphere({0, 0, 0}, 50));
    renderables.push_back(new Plane({0, -50, 0}));

    BMP bmp2(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            Vec3 centeredCoordinates = Vec3{x - SCREEN_WIDTH / 2.0f, y - SCREEN_HEIGHT / 2.0f, 0};
            Ray ray{origin : camera->position, direction : (camera->ZoomedDirection() + centeredCoordinates).Normalized()};

            float depth = March(ray);
            Vec3 intersectionPoint = ray.origin + ray.direction * depth;

            float diffuseColor = GetDiffuseColor(intersectionPoint);
            if (diffuseColor < 0)
                diffuseColor = 0;
            if (diffuseColor < AMBIENT_LIGHT)
                diffuseColor = AMBIENT_LIGHT;
            float normalizedDiffuseColor = diffuseColor * 255;
            if (normalizedDiffuseColor > 255)
                normalizedDiffuseColor = 255;

            Color c{normalizedDiffuseColor, normalizedDiffuseColor, normalizedDiffuseColor};

            bmp2.set_pixel(x, y, c.b(), c.g(), c.r(), c.a());
        }
    }
    bmp2.write("Ray-tracer/res/ray_traced_frame.bmp");

    delete camera;
    delete light;
    for (auto r : renderables)
    {
        delete r;
    }
    renderables.clear();
}