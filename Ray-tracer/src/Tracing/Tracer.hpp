#include <iostream>
#include <vector>
#include "bmp.hpp"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Tracing/Ray.h"
#include "Tracing/Hit.h"
#include "Objects/Renderable.h"
#include "Objects/Camera.h"
#include "Objects/Light.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"

class Tracer
{
	const Vec2 SCREEN_SIZE = {1280, 720};
	const Vec2 CLIP_PLANES = {1, 2000};
	const float MAX_SHADOW_DISTANCE = 500.0f;
	const uint8_t MAX_REFLECTIONS = 8;
	const uint8_t REFLECTION_THRESHOLD = 1;
	const float REFLECTION_BIAS = 0.005f;

	Camera* camera;
	Light* light;
	std::vector<Object*> objects;
	std::vector<Renderable*> renderables;

	Hit Trace(const Ray& ray)
	{
		Hit bestHit = Hit{{0,0,0}, {0,0,0}, CLIP_PLANES.y, {0}};
		for (auto r : renderables)
		{
			Hit hit = r->Intersect(ray);
			if (hit.distance > 0 && hit.distance < bestHit.distance) bestHit = hit;
		}
		return bestHit;
	}

	Color Shade(Ray& ray, const Hit& hit, const Light& light)
	{
		Color color;
		if (hit.distance < ray.lenght)
		{
			ray.origin = hit.position + hit.normal * REFLECTION_BIAS;
			ray.direction = Reflect(ray.direction, hit.normal);
			ray.energy = ray.energy * hit.object->specularColor;

			Vec3 directionToLight = (light.position - hit.position).Normalized();
			Ray shadowRay;
			shadowRay.origin = hit.position + hit.normal * light.bias;
			shadowRay.direction = directionToLight;
			shadowRay.lenght = MAX_SHADOW_DISTANCE;

			float shadowHitDistance = Trace(shadowRay).distance;
			float diffuseLight = shadowHitDistance < shadowRay.lenght ? 0.1f : Dot(hit.normal, directionToLight) + 0.2f;

			float multiplier = diffuseLight * light.intensity;
			
			if (multiplier < 0) multiplier = 0;
			else if (multiplier > 1) multiplier = 1;

			color = hit.object->color * multiplier;
		}
		else
		{
			ray.energy = 0;
			color = 0;
			// get color from skybox;
		}
		
		return color;
	}

	void Initialize()
	{
		objects.push_back(new Camera(Vec3{0, 0.5f, -5}, Vec3{0, 0, 1}, 700));
		camera = (Camera*)objects.back();
		objects.push_back(new Light(Vec3{500, 300, -300}, 2.0f, 0.005f));
		light = (Light*)objects.back();

		objects.push_back(new Sphere{{-1,0,0}, 1, {50,10,10, 0xff}, {120,120,120}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Sphere{{1,-0.25f,-0.5f}, 0.7f, {10, 20, 50, 0xff}, {30,30,30}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Plane({1, -1, 0}, {0,1,0}, {100, 100, 100, 0xff}, {10, 10, 10}));
		renderables.push_back((Renderable*)objects.back());

	}

	void Deinitialize()
	{
		for (const auto& o : objects)
		{
			Object* sphere = (Object*)objects[2];
			delete o;
		}
		renderables.clear();
		objects.clear();
	}

public:
	void Run()
	{
		Initialize();

		BMP bmp2(SCREEN_SIZE.x, SCREEN_SIZE.y);
		for (int y = 0; y < SCREEN_SIZE.y; y++)
		{
			for (int x = 0; x < SCREEN_SIZE.x; x++)
			{
				Vec3 normalizedUV = Vec3{x - SCREEN_SIZE.x / 2.0f, y - SCREEN_SIZE.y / 2.0f, 0};
				Ray ray = camera->CreateRay(normalizedUV, CLIP_PLANES);
				
				Color resultColor;
				for (int i = 0; i < MAX_REFLECTIONS; i++)
				{
					Hit bestHit = Trace(ray);
					Color rayEnergy = ray.energy;
					resultColor = resultColor + rayEnergy * Shade(ray, bestHit, *light);

					if (resultColor.r() <= REFLECTION_THRESHOLD
					|| resultColor.g() <= REFLECTION_THRESHOLD
					|| resultColor.b() <= REFLECTION_THRESHOLD)
						break;
				}
				resultColor.a(0xff);

				bmp2.set_pixel(x, y, resultColor.b(), resultColor.g(), resultColor.r(), resultColor.a());
			}
		}
		bmp2.write("Ray-tracer/res/ray_traced_frame.bmp");

		Deinitialize();
	}
};