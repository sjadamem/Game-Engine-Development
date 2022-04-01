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