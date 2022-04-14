#pragma once

#include "matrix4d.h"

struct Transform4d : Matrix4d
{
	Transform4d() = default;
	Transform4d(
		float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23
	)
	{
		n[0][0] = n00;	n[1][0] = n01;	n[2][0] = n02;	n[3][0] = n03;

		n[0][1] = n10;	n[1][1] = n11;	n[2][1] = n12;	n[3][1] = n13;

		n[0][2] = n20;	n[1][2] = n21;	n[2][2] = n22;	n[3][2] = n23;

		n[0][3] =		n[1][3] =		n[2][3] = 0.0F;	n[3][3] = 1.0F;
	}

	Transform4d(const Vector3d& a, const Vector3d& b, const Vector3d& c, const Point3d& p)
	{
		n[0][0] = a.x;	n[1][0] = b.x;	n[2][0] = c.x;	n[3][0] = p.x;

		n[0][1] = a.y;	n[1][1] = b.y;	n[2][1] = c.y;	n[3][1] = p.y;

		n[0][2] = a.z;	n[1][2] = b.z;	n[2][2] = c.z;	n[3][2] = p.z;

		n[0][3] =		n[1][3] =		n[2][3] = 0.0F;	n[3][3] = 1.0F;
	}

	Vector3d& operator[] (int j)
	{
		return (*reinterpret_cast<Vector3d*>(n[j]));
	}

	const Vector3d& operator[] (int j) const
	{
		return (*reinterpret_cast<const Vector3d*>(n[j]));
	}

	const Point3d& GetTranslation(void) const
	{
		return (*reinterpret_cast<const Point3d*>(n[3]));
	}

	void SetTranslation(const Point3d& p)
	{
		n[3][0] = p.x;
		n[3][1] = p.y;
		n[3][2] = p.z;
	}
};

Transform4d operator* (const Transform4d& a, const Transform4d& b)
{
	return Transform4d(
		a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),				//n00
		a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),				//n01
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),				//n02
		a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 3) + a(0, 3),	//n02

		a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),				//n10
		a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),				//n11
		a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),				//n12
		a(1, 0) * b(0, 3) + a(1, 1) * b(1, 3) + a(1, 2) * b(2, 3) + a(1, 3),	//n12

		a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),				//n20
		a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),				//n21
		a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),				//n22
		a(2, 0) * b(0, 3) + a(2, 1) * b(1, 3) + a(2, 2) * b(2, 3) + a(2, 3)		//n22
	);
}

Vector3d operator* (const Transform4d& H, const Vector3d& v)
{
	return Vector3d(
		H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
		H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
		H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z
	);
}

Point3d operator* (const Transform4d& H, const Point3d& p)
{
	return Point3d(
		H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
		H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
		H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3)
	);
}

Transform4d inverse(const Transform4d& H)
{
	/*
	H = [ M^-1		-M^-1*t ]
		[ 0			1		]
	*/
	const Vector3d& a = H[0];
	const Vector3d& b = H[1];
	const Vector3d& c = H[2];
	const Vector3d& d = H[3];

	Vector3d s = cross(a, b);
	Vector3d t = cross(c, d);

	float invDet = 1.0F / dot(s, c);

	s *= invDet;
	t *= invDet;
	Vector3d v = c * invDet;

	Vector3d r0 = cross(b, v);
	Vector3d r1 = cross(v, a);

	return Transform4d(
		r0.x,	r0.y,	r0.z,	-dot(b, t),		//[	[(b x c).x]/det(M)	[(b x c).y]/det(M)	[(b x c).z]/det(M)	-[(b x c)*d]/det(M)	]
		r1.x,	r1.y,	r1.z,	 dot(a, t),		//[	[(c x a).x]/det(M)	[(c x a).y]/det(M)	[(c x a).z]/det(M)	-[(c x a)*d]/det(M)	]
		s.x,	s.y,	s.z,	-dot(d, s)		//[	[(a x b).x]/det(M)	[(a x b).y]/det(M)	[(a x b).z]/det(M)	-[(a x b)*d]/det(M)	]
	);
}