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

	Color Shade(const Hit& hit, const Light& light)
	{
		Vec3 directionToLight = (light.position - hit.position).Normalized();
		Ray ray;
		ray.origin = hit.position + hit.normal * light.bias;
		ray.direction = directionToLight;
		ray.lenght = MAX_SHADOW_DISTANCE;

		float shadowHitDistance = Trace(ray).distance;

		float shadowLight = shadowHitDistance < ray.lenght ? 0.35f : 1.0f;
		float diffuseLight = Dot(hit.normal, directionToLight);

		float multiplier = shadowLight * diffuseLight;
		if (multiplier < 0) multiplier = 0;
		else if (multiplier > 1) multiplier = 1;

		Color color = hit.color * multiplier;
		color.a(hit.color.a());
		return color;
	}

public:
	void Run()
	{
		objects.push_back(new Camera(Vec3{5, 0, 0}, Vec3{-1, 0, 0}, 700));
		camera = (Camera*)objects.back();
		objects.push_back(new Light(Vec3{500, 300, 400}, 0.01f));
		light = (Light*)objects.back();

		objects.push_back(new Sphere{{0,0,0}, 1, {255, 50, 50, 0xff}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Plane({1, -1, 0}, {0,1,0}, {127, 127, 255, 0xff}));
		renderables.push_back((Renderable*)objects.back());

		for (int i = 0; i < objects.size(); i++)
		{
			const auto& o = objects[i];
			std::cout<<o;
		}

		BMP bmp2(SCREEN_SIZE.x, SCREEN_SIZE.y);
		for (int y = 0; y < SCREEN_SIZE.y; y++)
		{
			for (int x = 0; x < SCREEN_SIZE.x; x++)
			{
				Vec3 normalizedUV = Vec3{x - SCREEN_SIZE.x / 2.0f, y - SCREEN_SIZE.y / 2.0f, 0};
				Ray ray = camera->CreateRay(normalizedUV, CLIP_PLANES);

				Hit bestHit = Trace(ray);
				Color resultColor =  Shade(bestHit, *light);

				bmp2.set_pixel(x, y, resultColor.b(), resultColor.g(), resultColor.r(), resultColor.a());
			}
		}

		bmp2.write("Ray-tracer/res/ray_traced_frame.bmp");

		for (const auto& o : objects)
		{
			Object* sphere = (Object*)objects[2];
			delete o;
		}
		renderables.clear();
		objects.clear();
	}
};