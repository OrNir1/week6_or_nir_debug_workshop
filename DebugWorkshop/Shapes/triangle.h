#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "shape.h"

class Triangle : public Shape 
{
private:
	float _base;
	float _height;
public:
	Triangle(float base, float height);
	float get_area() const override;
	float get_area_with_depth(bool has_depth = false) const;

};


#endif	// __TRIANGLE_H__
