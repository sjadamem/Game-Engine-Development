#pragma once

#include <math.h>

struct Vector4d
{
	float x, y, z, w;

	Vector4d() = default;

	Vector4d(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
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

	Vector4d& operator*= (float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;
		return (*this);
	}

	Vector4d& operator/= (float s)
	{
		s = 1.0F / s;
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;
		return (*this);
	}

	Vector4d operator+= (const Vector4d& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return (*this);
	}

	Vector4d operator-= (const Vector4d& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return (*this);
	}
};