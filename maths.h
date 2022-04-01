#pragma once

#include <math.h>

struct Vector3d
{
	float x, y, z;

	Vector3d() = default;

	Vector3d(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float& operator[](int index)
	{
		return ((&x)[index]);	//returns the value located at the address of the first value of this vector + (index - 1) * float bytes
		//TO-DO: Implement out-of-bounds checks when the index is greater than the amount of values in this vector
	}

	const float& operator[](int index) const
	{
		return ((&x)[index]);
	}

	Vector3d& operator*= (float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return (*this);
	}

	Vector3d& operator/= (float s)
	{
		s = 1.0F / s;
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return (*this);
	}

	Vector3d operator+= (const Vector3d& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vector3d operator-= (const Vector3d& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}
};

inline Vector3d operator* (const Vector3d& v, float s)
{
	return (Vector3d(v.x * s, v.y * s, v.z * s));
}

inline Vector3d operator/ (const Vector3d& v, float s)
{
	s = 1.0F / s;
	return v * s;
}

inline Vector3d operator- (const Vector3d& v)
{
	return Vector3d(-v.x, -v.y, -v.z);
}

inline float magnitude(const Vector3d& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3d normalize(const Vector3d& v)
{
	return v / magnitude(v);
}

inline Vector3d operator+ (const Vector3d& a, const Vector3d& b)
{
	return Vector3d(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3d operator- (const Vector3d& a, const Vector3d& b)
{
	return a + (-b);
}

struct Matrix3d
{
	float n[3][3];

	Matrix3d() = default;

	Matrix3d(
		float x0, float x1, float x2,
		float y0, float y1, float y2,
		float z0, float z1, float z2
	)
	{
		n[0][0] = x0;
		n[1][0] = x1;
		n[2][0] = x2;
		n[0][1] = y0;
		n[1][1] = y1;
		n[2][1] = y2;
		n[0][2] = z0;
		n[1][2] = z1;
		n[2][2] = z2;
	}

	Matrix3d(const Vector3d& a, const Vector3d& b, const Vector3d& c)
	{
		n[0][0] = a.x;
		n[1][0] = b.x;
		n[2][0] = c.x;
		n[0][1] = a.y;
		n[1][1] = b.y;
		n[2][1] = c.y;
		n[0][2] = a.z;
		n[1][2] = b.z;
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