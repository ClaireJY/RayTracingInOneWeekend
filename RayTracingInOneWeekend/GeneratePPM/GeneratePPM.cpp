// GeneratePPM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "color.h"

using namespace std;

hitable_list random_scene();
color ray_color(ray& r, hitable_list world, int depth)
{
	hit_record rec;
	if (depth <= 0)
		return color(0, 0, 0);
	if(world.hit(r, 0.001f, FLT_MAX, rec))
	{
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}
		else
		{
			return color(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5f * (unit_direction.y() + 1.0f);
		return  color(1.0, 1.0, 1.0)* (1.0 - t) + color(0.5, 0.7, 1.0) * t;
	}
	
}


void GenerateRayTracingImage()
{
	int image_width = 1200;
	const auto aspect_ratio = 3.0 / 2.0;
	int image_height = static_cast<int>(image_width / aspect_ratio);
	int samples_per_pixel = 50;
	const int max_depth = 50;
	ofstream ppmfile;
	ppmfile.open("ppmtest.ppm");
	ppmfile << "P3\n" << image_width << " " << image_height << "\n255\n";
	
	hitable_list world = random_scene();

	
	point3 lookfrom(13, 2, 2);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	double dist_to_focus = 10.0;
	double aperture = 2.0;
	camera cam(lookfrom, lookat, vup,20, aspect_ratio,aperture, dist_to_focus);
	for (int j = image_height - 1; j >= 0; j--)
	{
		cout << "Scan lines remaining " << j << endl << flush;
		for (int i = 0; i < image_width; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				
				double u = double(i + random_double()) / double(image_width);
				double v = double(j + random_double()) / double(image_height);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += ray_color(r, world, max_depth);
			}
			

			col /= double(samples_per_pixel);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			write_color(ppmfile, col);
		}
	}
}

hitable_list random_scene()
{
	hitable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
			if ((center - point3(4, 0.2, 0)).length() > 0.9)
			{
				shared_ptr<material> sphere_material;
				if (choose_mat < 0.8)
				{
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					auto allbedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(allbedo, fuzz);
				}
				else
				{
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
	auto material2 = make_shared<lambertian>(color(0.4,0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
	auto material3 = make_shared<metal>(color(0.7, 0.6,0.5), 0.5);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


int main()
{
	//GenerateRGBImage();
	GenerateRayTracingImage();
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
