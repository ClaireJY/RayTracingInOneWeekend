#pragma once
#include "ray.h"
using namespace std;
class material;

struct  hit_record
{
	double t;
	point3 p;
	vec3 normal;
	shared_ptr<material> mat_ptr;
};

class hitable {
public :
	virtual bool hit(ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};