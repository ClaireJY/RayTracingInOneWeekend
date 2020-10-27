#pragma once

#include "ray.h"

class camera {
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, float apeture, float focus_dist) {
		lens_radius = aspect / 2;
		double theta = vfov * pi / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;

		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = half_width * u * 2;
		vertical = half_height * v * 2;
	}

	ray get_ray(double s, double t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
	}


	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};