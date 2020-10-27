#pragma once

#include "hitable.h"

class sphere :public hitable
{
public:
	sphere() {}

	sphere(point3 cen, double r, shared_ptr<material> mat) :center(cen), radius(r), mat_ptr(mat) {};
	virtual bool hit(ray& r, double t_min, double t_max, hit_record& rec)const;

	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

bool sphere::hit(ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		rec.mat_ptr = mat_ptr;
		double temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

	}

	return false;
}
