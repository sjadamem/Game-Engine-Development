#pragma once

#include <math.h>

#include "vector3d.h"

struct Matrix3d
{
private:
	//		y  x
	float n[3][3];

public:
	Matrix3d() = default;

	Matrix3d(
		float n00, float n01, float n02,
		float n10, float n11, float n12,
		float n20, float n21, float n22
	)
	{
		n[0][0] = n00;	
		n[0][1] = n10;	
		n[0][2] = n20;
		
		n[1][0] = n01;	
		n[1][1] = n11;	
		n[1][2] = n21;
		
		n[2][0] = n02;	
		n[2][1] = n12;	
		n[2][2] = n22;
	}

	Matrix3d(const Vector3d& a, const Vector3d& b, const Vector3d& c)
	{
		n[0][0] = a.x;
		n[0][1] = a.y;
		n[0][2] = a.z;
		
		n[1][0] = b.x;
		n[1][1] = b.y;
		n[1][2] = b.z;
		
		n[2][0] = c.x;
		n[2][1] = c.y;
		n[2][2] = c.z;
	}

	float& operator() (int i, int j)
	{
		return (n[j][i]);
	}

	const float& operator() (int i, int j) const
	{
		return (n[j][i]);
	}

	Vector3d& operator[] (int j)
	{
		return (*reinterpret_cast<Vector3d*>(n[j]));
	}

	const Vector3d& operator[] (int j) const
	{
		return (*reinterpret_cast<const Vector3d*>(n[j]));
	}
};

Matrix3d operator*(const Matrix3d& a, const Matrix3d& b)
{
	return Matrix3d(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2)
	);
}

Vector3d operator*(const Matrix3d& m, const Vector3d& v)
{
	return Vector3d(
		m(0, 0) * v[0] + m(0, 1) * v[1] + m(0, 2) * v[2],
		m(1, 0) * v[0] + m(1, 1) * v[1] + m(1, 2) * v[2],
		m(2, 0) * v[0] + m(2, 1) * v[1] + m(2, 2) * v[2]
	);
}