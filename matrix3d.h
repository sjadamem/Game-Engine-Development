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
		n[0][0] = n00;	n[1][0] = n01;	n[2][0] = n02;

		n[0][1] = n10;	n[1][1] = n11;	n[2][1] = n12;

		n[0][2] = n20;	n[1][2] = n21;	n[2][2] = n22;
	}

	Matrix3d(const Vector3d& a, const Vector3d& b, const Vector3d& c)
	{
		n[0][0] = a.x;	n[1][0] = b.x;	n[2][0] = c.x;
		n[0][1] = a.y;	n[1][1] = b.y;	n[2][1] = c.y;
		n[0][2] = a.z;	n[1][2] = b.z;	n[2][2] = c.z;
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

Matrix3d operator-(const Matrix3d& a)
{
	return Matrix3d(
		-a(0,0),	-a(0,1),	-a(0,2),
		-a(1,0),	-a(1,1),	-a(1,2),
		-a(2,0),	-a(2,1),	-a(2,2)
	);
}

Matrix3d operator+(const Matrix3d& a, const Matrix3d& b)
{
	return Matrix3d(
		a(0, 0) + b(0, 0),	a(0, 1) + b(0, 1),	a(0, 2) + b(0, 2),
		a(1, 0) + b(1, 0),	a(1, 1) + b(1, 1),	a(1, 2) + b(1, 2),
		a(2, 0) + b(2, 0),	a(2, 1) + b(2, 1),	a(2, 2) + b(2, 2)
	);
}

Matrix3d operator-(const Matrix3d& a, const Matrix3d& b)
{
	return a + (-b);
}

Matrix3d operator*(const Matrix3d& a, float b)
{
	return Matrix3d(
		a(0, 0) * b,
		a(0, 1) * b,
		a(0, 2) * b,
		a(1, 0) * b,
		a(1, 1) * b,
		a(1, 2) * b,
		a(2, 0) * b,
		a(2, 1) * b,
		a(2, 2) * b
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

Matrix3d operator* (const Matrix3d& a, const Matrix3d& b)
{
	return Matrix3d(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),				//n00
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),				//n01
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),				//n02

		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),				//n10
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),				//n11
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),				//n12

		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),				//n20
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),				//n21
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2)				//n22
	);
}

inline Matrix3d identity()
{
	return Matrix3d(
		1.0F,	0.0F,	0.0F,
		0.0F,	1.0F,	0.0F,
		0.0F,	0.0F,	1.0F
	);
}

float determinant(const Matrix3d& m)
{
	return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) 
		 + m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2))
		 + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
}

Matrix3d inverse(const Matrix3d& m)
{
	const Vector3d& a = m[0];
	const Vector3d& b = m[1];
	const Vector3d& c = m[2];

	Vector3d r0 = cross(b, c);
	Vector3d r1 = cross(c, a);
	Vector3d r2 = cross(a, b);

	float invDet = 1.0F / dot(r2, c);

	return Matrix3d(
		r0.x, r0.y, r0.z,
		r1.x, r1.y, r1.z,
		r2.x, r2.y, r2.z
	) * invDet;
}

/*
Rotation functions not working how I expected. Need to do some more research.
*/
Matrix3d rotateX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

	return Matrix3d(
		1.0F,	0.0F,	0.0F,
		0.0F,	c,		s,
		0.0F,	-s,		c
	);
}

//corrected returning matrix3d
Matrix3d rotateY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

	return Matrix3d(
		c,		0.0F,	-s,
		0.0F,	1.0F,	0.0F,
		s,		0.0F,	c
	);
}

//corrected returning matrix3d
Matrix3d rotateZ(float angle)
{
	float c = cos(angle);
	float s = sin(angle);

	return Matrix3d(
		c,		s,		0.0F,
		-s,		c,		0.0F,
		0.0F,	0.0F,	1.0F
	);
}

Matrix3d rotate(const Vector3d& r)
{
	return rotateZ(r.z) * rotateY(r.y) * rotateX(r.x);
}

Matrix3d rotateTowards(float angle, const Vector3d& a)
{
	float c = cos(angle);
	float s = sin(angle);
	float d = 1 - c;

	float x = a.x * d;
	float y = a.y * d;
	float z = a.z * d;

	float axay = x * a.y;	//a.x * a.y * (1 - cos)
	float axaz = x * a.z;	//a.x * a.z * (1 - cos)
	float ayaz = y * a.z;	//a.y * a.z * (1 - cos)

	return Matrix3d(
		c + x * a.x,		axay - s * a.z,		axaz + s * a.y,
		axay + s * a.z,		c + y * a.y,		ayaz - s * a.x,
		axaz - s * a.y,		ayaz + s * a.x,		c + z * a.z
	);
}

Matrix3d scale(float sx, float sy, float sz)
{
	return Matrix3d(
		sx, 0, 0,
		0, sy, 0,
		0, 0, sz
	);
}

Matrix3d scale(const Vector3d& s)
{
	return Matrix3d(
		s.x, 0, 0,
		0, s.y, 0,
		0, 0, s.z
	);
}

Matrix3d scaleTowards(float s, const Vector3d& a)
{
	s -= 1.0F;

	float x = a.x * s;
	float y = a.y * s;
	float z = a.z * s;

	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3d(
		x * a.x + 1.0F, axay, axaz,
		axay, y * a.y + 1.0F, ayaz,
		axaz, ayaz, z * a.z + 1.0F
	);
}

#if 0
Matrix3d skew()
{
	return Matrix3d();
}
#endif

Matrix3d reflect(const Vector3d& a)
{
	float x = -2.0F * a.x;
	float y = -2.0F * a.y;
	float z = -2.0F * a.z;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3d(
		x * a.x + 1.0F,		axay,				axaz,
		axay,				y * a.y + 1.0F,		ayaz,
		axaz,				ayaz,				z * a.z + 1.0F
	);
}

#if 0
Matrix3d involution(const Vector3d& a)
{
	float x = 2.0F * a.x;
	float y = 2.0F * a.y;
	float z = 2.0F * a.z;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return Matrix3d(
		x * a.x - 1.0F, axay, axaz,
		axay, y * a.y - 1.0F, ayaz,
		axaz, ayaz, z * a.z - 1.0F
	);
}
#endif

Matrix3d involution(const Vector3d& a)
{
	return reflect(a) * -1.0F;
}