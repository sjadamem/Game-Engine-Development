#pragma once

#include "vector3d.h"

struct Point3d : Vector3d
{
	Point3d() = default;

	Point3d(float x, float y, float z) : Vector3d(x, y, z) {}
};

inline Point3d operator- (const Point3d& p)
{
	return Point3d(-p.x, -p.y, -p.z);
}

inline Point3d operator+ (const Point3d& a, const Point3d& b)
{
	return Point3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Point3d operator- (const Point3d& a, const Point3d& b)
{
	return a + (-b);
}