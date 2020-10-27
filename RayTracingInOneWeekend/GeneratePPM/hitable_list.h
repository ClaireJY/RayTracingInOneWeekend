#pragma once

#include "hitable.h"

class hitable_list :public hitable
{
public:
	hitable_list(){}
	hitable_list(shared_ptr<hitable> object) { add(object); }
	virtual bool hit(ray& r, double tmin, double tmax, hit_record& rec)const;
	void add(shared_ptr<hitable> object) { objects.push_back(object); }
	void clear() { objects.clear(); }
	
	vector<shared_ptr<hitable>> objects;
};

bool hitable_list::hit(ray& r, double t_min, double t_max, hit_record& rec) const 
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (const auto& object: objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
