#ifndef MATH_H
#define MATH_H

#include <cmath>
#include "Vectors.h"

namespace Math
{
	/// <summary>
	/// PI (3.14159...)
	/// </summary>
	const float PI = std::atan(1.0f) * 4;
	const float TWO_PI = 2 * PI;

	float dot(const Vector4& a, const Vector4& b);
	float dot(const Vector3& a, const Vector3& b);
}

#endif

