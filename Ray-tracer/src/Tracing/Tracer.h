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

	Camera* camera;
	Light* light;
	std::vector<Object*> objects;
	std::vector<Renderable*> renderables;

public:
	void Run()
	{
		objects.push_back(new Camera(Vec3{0, 1, -5}, Vec3{0, 0, 1}, 700));
		camera = (Camera*)objects.back();
		objects.push_back(new Light(Vec3{500, 300, 0}));
		light = (Light*)objects.back();

		objects.push_back(new Sphere{{0,0,0}, 1, {255, 127, 127, 0xff}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Plane({0, -1, 0}, {0,1,0}, {127, 255, 127, 0xff}));
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
				Hit bestHit = Hit{{0,0,0}, {0,0,0}, CLIP_PLANES.y, {0}};

				for (auto r : renderables)
				{
					Hit hit = r->Intersect(ray);
					if (hit.distance > 0 && hit.distance < bestHit.distance) bestHit = hit;
				}

				// apply lighting at best hit position
				bmp2.set_pixel(x, y, bestHit.color.b(), bestHit.color.g(), bestHit.color.r(), bestHit.color.a());
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