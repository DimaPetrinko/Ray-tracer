#include <iostream>
#include <vector>
#include <chrono>
#include "bmp.hpp"
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Tracing/Ray.h"
#include "Tracing/Hit.h"
#include "Assets/Texture.h"
#include "Objects/Renderable.h"
#include "Objects/Camera.h"
#include "Objects/Light.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"

class Tracer
{
	const Vec2 SCREEN_SIZE = {1280, 720};
	const Vec2 CLIP_PLANES = {1, 2000};
	const float SHADOW_DIFFUSE = 0.0f;
	const float MAX_SHADOW_DISTANCE = 500.0f;
	const uint8_t MAX_REFLECTIONS = 8;
	const uint8_t REFLECTION_THRESHOLD = 1;
	const float REFLECTION_BIAS = 0.005f;
	const float PI = 3.14159265359f;

	Camera* camera;
	Light* light;
	Texture* skyboxTexture;
	Texture* outputTexture;
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

	Color Shade(Ray& ray, const Hit& hit, const Light& light, const Texture* skyboxTexture)
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
			float diffuseLight = shadowHitDistance < shadowRay.lenght
				? SHADOW_DIFFUSE
				: Dot(hit.normal, directionToLight) / 2 + SHADOW_DIFFUSE;

			float multiplier = diffuseLight * light.intensity;
			
			if (multiplier < 0) multiplier = 0;
			else if (multiplier > 1) multiplier = 1;

			color = hit.object->color * multiplier;
		}
		else
		{
			ray.energy = 0;
			float theta = acos(ray.direction.y) / -PI;
			float phi = atan2(ray.direction.x, -ray.direction.z) / -PI * 0.5f;
			color = skyboxTexture->GetPixel(Vec2{phi, theta});
		}
		
		return color;
	}

	Color ProcessPixel(const int& u, const int& v)
	{
		Vec3 normalizedUV = Vec3{u - SCREEN_SIZE.x / 2.0f, v - SCREEN_SIZE.y / 2.0f, 0};
		Ray ray = camera->CreateRay(normalizedUV, CLIP_PLANES);
		
		Color resultColor;
		for (int i = 0; i < MAX_REFLECTIONS; i++)
		{
			Hit bestHit = Trace(ray);
			Color rayEnergy = ray.energy;
			resultColor = resultColor + rayEnergy * Shade(ray, bestHit, *light, skyboxTexture);

			if (rayEnergy.r() <= REFLECTION_THRESHOLD
			|| rayEnergy.g() <= REFLECTION_THRESHOLD
			|| rayEnergy.b() <= REFLECTION_THRESHOLD)
				break;
		}
		resultColor.a(0xff);
		return resultColor;
	}

	void LoadAssets()
	{
		skyboxTexture = new Texture("Ray-tracer/res/skybox.bmp");
		outputTexture = new Texture(SCREEN_SIZE.x, SCREEN_SIZE.y);
	}

	void UnloadAssets()
	{
		delete skyboxTexture;
		delete outputTexture;
	}

	void Initialize()
	{
		LoadAssets();

		objects.push_back(new Camera(Vec3{0, 0.5f, -5}, Vec3{0, 0, 1}, 700));
		camera = (Camera*)objects.back();
		objects.push_back(new Light(Vec3{500, 300, -300}, 1.0f, 0.0001f));
		light = (Light*)objects.back();

		objects.push_back(new Sphere{{-1,0,0}, 1, {50,10,10, 0xff}, {255,200,120}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Sphere{{1,-0.25f,-0.5f}, 0.7f, {10, 20, 50, 0xff}, {30,50,80}});
		renderables.push_back((Renderable*)objects.back());
		objects.push_back(new Plane({1, -1, 0}, {0,1,0}, {100, 100, 100, 0xff}, {50, 50, 50}));
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

		UnloadAssets();
	}

public:
	void Run()
	{
		Initialize();

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		for (int y = 0; y < SCREEN_SIZE.y; y++)
		{
			for (int x = 0; x < SCREEN_SIZE.x; x++)
			{
				Color resultColor = ProcessPixel(x, y);
				outputTexture->SetPixel(x, y, resultColor);
			}
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
		outputTexture->Save("Ray-tracer/res/ray_traced_frame.bmp");

		Deinitialize();
	}
};