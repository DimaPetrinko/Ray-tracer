#include <iostream>
#include <cmath>
#include "bmp.hpp"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Tracing/Ray.h"
#include "Tracing/Color.h"
#include "Tracing/Tracer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const Vec2 CLIP_PLANES = {1, 2000};
const int MAX_STEPS = 100;
const float MIN_DISTANCE = 0.01f;
const float AMBIENT_LIGHT = 0.1f;
const float SHADOW_BIAS = 0.5f;

int FlattenIndex(int x, int y, int width)
{
    return y * width + x;
}

float GetDiffuseColor(const Vec3 &point)
{
    // Vec3 directionToLight = (light->position - point);
    // Vec3 directionToLightNormalized = directionToLight.Normalized();
    // Vec3 surfaceNormal = GetNormal(point);
    // float diffuse = Dot(surfaceNormal, directionToLightNormalized);

    // float distanceToLight = March({point + surfaceNormal, directionToLightNormalized});
    // if (distanceToLight < directionToLight.Magnitude())
    //     diffuse *= AMBIENT_LIGHT;

    // return diffuse;
}

int main()
{
    Tracer tracer = Tracer();
    tracer.Run();
    return 0;
    // camera = new Camera{position : {0, 25, -300}, direction : {0, 0, 1}, up : {}, zoom : 700};
    // light = new PointLight{{500, 300, 0}};

    // renderables.push_back(new Sphere({0, 0, 0}, 50));
    // renderables.push_back(new Plane({0, -50, 0}));

    // BMP bmp2(SCREEN_WIDTH, SCREEN_HEIGHT);
    // for (int y = 0; y < SCREEN_HEIGHT; y++)
    // {
    //     for (int x = 0; x < SCREEN_WIDTH; x++)
    //     {
    //         Vec3 centeredCoordinates = Vec3{x - SCREEN_WIDTH / 2.0f, y - SCREEN_HEIGHT / 2.0f, 0};
    //         Ray ray{origin : camera->position, direction : (camera->ZoomedDirection() + centeredCoordinates).Normalized()};

    //         float depth = March(ray);
    //         Vec3 intersectionPoint = ray.origin + ray.direction * depth;

    //         float diffuseColor = GetDiffuseColor(intersectionPoint);

    //         if (diffuseColor < 0)
    //             diffuseColor = 0;
    //         if (diffuseColor < AMBIENT_LIGHT)
    //             diffuseColor = AMBIENT_LIGHT;

    //         float normalizedDiffuseColor = diffuseColor * 255;

    //         if (normalizedDiffuseColor > 255)
    //             normalizedDiffuseColor = 255;

    //         Color c{normalizedDiffuseColor, normalizedDiffuseColor, normalizedDiffuseColor};

    //         bmp2.set_pixel(x, y, c.b(), c.g(), c.r(), c.a());
    //     }
    // }
    // bmp2.write("Ray-tracer/res/ray_traced_frame.bmp");

    // delete camera;
    // delete light;
    // for (auto r : renderables)
    // {
    //     delete r;
    // }
    // renderables.clear();
}