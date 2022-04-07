#pragma once

#include <math.h>

#include "vector3d.h"
#include "vector4d.h"

struct Matrix4d
{
private:
	//		y  x
	float n[4][4];

public:
	Matrix4d() = default;

	Matrix4d(
		float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33
	)
	{
		n[0][0] = n00;
		n[0][1] = n10;
		n[0][2] = n20;
		n[0][3] = n30;

		n[1][0] = n01;
		n[1][1] = n11;
		n[1][2] = n21;
		n[1][3] = n31;

		n[2][0] = n02;
		n[2][1] = n12;
		n[2][2] = n22;
		n[2][3] = n32;

		n[3][0] = n03;
		n[3][1] = n13;
		n[3][2] = n23;
		n[3][3] = n33;
	}

	float& operator() (int i, int j)
	{
		return (n[j][i]);
	}

	const float& operator() (int i, int j) const
	{
		return (n[j][i]);
	}

	Vector4d& operator[] (int j)
	{
		return (*reinterpret_cast<Vector4d*>(n[j]));
	}

	const Vector4d& operator[] (int j) const
	{
		return (*reinterpret_cast<const Vector4d*>(n[j]));
	}
};

Matrix4d operator*(const Matrix4d& a, const Matrix4d& b)
{
	return Matrix4d(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0) + a(0, 3) * b(3, 0),	//n00
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1) + a(0, 3) * b(3, 1),	//n01
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2) + a(0, 3) * b(3, 2),	//n02
		a(0, 0) * b(0, 3) + a(0, 1) * b(1, 3) + a(0, 2) * b(2, 3) + a(0, 3) * b(3, 3),	//n03

		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0) + a(1, 3) * b(3, 0),	//n10
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1) + a(1, 3) * b(3, 1),	//n11
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2) + a(1, 3) * b(3, 2),	//n12
		a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3) * b(3, 2),	//n13

		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0) + a(2, 3) * b(3, 0),	//n20
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1) + a(2, 3) * b(3, 1),	//n21
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2) + a(2, 3) * b(3, 2),	//n22
		a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3) * b(3, 3),	//n23

		a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + a(3, 3) * b(3, 0),	//n30
		a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + a(3, 3) * b(3, 1),	//n31
		a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + a(3, 3) * b(3, 2),	//n32
		a(3, 0) * b(0, 3) + a(3, 1) * b(1, 3) + a(3, 2) * b(2, 3) + a(3, 3) * b(3, 3)	//n33
	);
}

Matrix4d operator*(const Matrix4d& a, float b)
{
	return Matrix4d(
		a(0, 0) * b,
		a(0, 1) * b,
		a(0, 2) * b,
		a(0, 3) * b,
		
		a(1, 0) * b,
		a(1, 1) * b,
		a(1, 2) * b,
		a(1, 3) * b,
		
		a(2, 0) * b,
		a(2, 1) * b,
		a(2, 2) * b,
		a(2, 3) * b,
		
		a(3, 0) * b,
		a(3, 1) * b,
		a(3, 2) * b,
		a(3, 3) * b
	);
}

inline Matrix4d identity()
{
	return Matrix4d(
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	);
}

#if 0
float determinant(const Matrix4d& m)
{
	return (m(0, 0) * m(1, 1) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1)) +
		(m(0, 1) * m(1, 2) * m(2, 0) - m(0, 1) * m(1, 0) * m(2, 2)) +
		(m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0));
}
#endif // 0

Matrix4d inverse(const Matrix4d& m)
{
	const Vector3d& a = reinterpret_cast<const Vector3d&>(m[0]);
	const Vector3d& b = reinterpret_cast<const Vector3d&>(m[1]);
	const Vector3d& c = reinterpret_cast<const Vector3d&>(m[2]);
	const Vector3d& d = reinterpret_cast<const Vector3d&>(m[3]);

	const float& x = m(3, 0);
	const float& y = m(3, 1);
	const float& z = m(3, 2);
	const float& w = m(3, 3);

	Vector3d s = cross(a, b);
	Vector3d t = cross(c, d);
	Vector3d u = a * y - b * x;
	Vector3d v = c * w - d * z;

	float invDet = 1.0F / (dot(s, v) + dot(t, u));
	s *= invDet;
	t *= invDet;
	u *= invDet;
	v *= invDet;

	Vector3d r0 = cross(b, v) + t * y;
	Vector3d r1 = cross(v, a) + t * x;
	Vector3d r2 = cross(d, u) + s * w;
	Vector3d r3 = cross(u, c) + s * z;

	return Matrix4d(
		r0.x, r0.y, r0.z, -dot(b, t),
		r1.x, r1.y, r1.z,  dot(a, t),
		r2.x, r2.y, r2.z, -dot(d, s),
		r3.x, r3.y, r3.z,  dot(c, s)
	);
}