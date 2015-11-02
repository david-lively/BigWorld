#include "Math.h"

/// <summary>
/// Returns the dot product of two Vectortors
/// </summary>
/// <param name="a">first Vectortor</param>
/// <param name="b">second Vectortor</param>
/// <returns></returns>
float Math::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/// <summary>
/// Returns the dot product of two Vectortors
/// </summary>
/// <param name="a">first Vectortor</param>
/// <param name="b">second Vectortor</param>
/// <returns></returns>
float Math::dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
