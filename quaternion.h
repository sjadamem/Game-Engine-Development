#pragma once

#include "vector3d.h"
#include "matrix3d.h"

struct Quaternion
{
	float x, y, z, w;

	Quaternion() = default;

	Quaternion(float a, float b, float c, float s)
	{
		x = a;
		y = b;
		z = c;
		w = s;
	}

	Quaternion(const Vector3d& v, float s)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = s;
	}

	const Vector3d& GetVector(void) const
	{
		return (reinterpret_cast<const Vector3d&>(x));
	}
	
	Matrix3d GetRotationMatrix(void);
	void SetRotationMatrix(const Matrix3d& m);
};

Quaternion operator*(const Quaternion& a, const Quaternion& b)
{
	return Quaternion(
		(a.x * b.w + a.y * b.z + a.w * b.x - a.z * b.y),
		(a.y * b.w + a.z * b.x + a.w * b.y - a.x * b.z),
		(a.x * b.y + a.z * b.w + a.w * b.z - a.y * b.x),
		(a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z)
	);
}

Matrix3d Quaternion::GetRotationMatrix(void)
{
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float xw = x * w;
	float yw = y * w;
	float zw = z * w;

	return Matrix3d(
		1.0F - 2.0F * (y2 + z2),	2.0F * (xy - zw),			2.0F * (xz + yw),
		2.0F * (xy + zw),			1.0F - 2.0F * (x2 + z2),	2.0F * (xy - xw),
		2.0F * (xz - yw),			2.0F * (yz + xw),			1.0F - 2.0F * (x2 + z2)
	);
}

void Quaternion::SetRotationMatrix(const Matrix3d& m)
{
	float m00 = m(0, 0);
	float m11 = m(1, 1);
	float m22 = m(2, 2);
	float sum = m00 + m11 + m22;

	if (sum > 0.0F)
	{
		w = sqrtf((sum + 1.0F)) * 0.5F;
		float f = 0.25F / w;

		x = (m(2, 1) - m(1, 2)) * f;
		y = (m(0, 2) - m(2, 0)) * f;
		z = (m(1, 0) - m(0, 1)) * f;
	}
	else if ((m00 > m11) && (m00 > m22))
	{
		x = sqrtf((m00 - m11 - m22 + 1.0F)) * 0.5F;
		float f = 0.25F / x;

		y = (m(1, 0) + m(0, 1)) * f;
		z = (m(0, 2) + m(2, 0)) * f;
		w = (m(2, 1) - m(1, 2)) * f;
	}
	else if (m11 > m22)
	{
		y = sqrtf((m11 - m00 - m22 + 1.0F)) * 0.5F;
		float f = 0.25F / y;

		x = (m(1, 0) + m(0, 1)) * f;
		z = (m(2, 1) + m(1, 2)) * f;
		w = (m(0, 2) + m(2, 0)) * f;
	}
	else
	{
		z = sqrtf((m22 - m00 - m11 + 1.0F)) * 0.5F;
		float f = 0.25F / z;

		x = (m(0, 2) + m(2, 0)) * f;
		y = (m(2, 1) + m(1, 2)) * f;
		w = (m(1, 0) - m(0, 1)) * f;
	}
}

Vector3d transform(const Vector3d& v, const Quaternion& q)
{
	const Vector3d& b = q.GetVector();
	float b2 = b.x * b.x + b.y * b.y + b.z * b.z;

	return (v * (q.w * q.w - b2) + b * (dot(v, b) * 2.0F) + cross(b, v) * (q.w * 2.0F));
}