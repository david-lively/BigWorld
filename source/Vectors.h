#ifndef VECTORS_H
#define VECTORS_H

#include <string>
#include <cmath>
#include "gl_core_4_5.hpp"

#pragma region templated vector types

using namespace std;

/// <summary>
/// Generic two-component Vectortor class
/// </summary>
template<typename T = GLfloat>
class TVector2
{


public:
	T x;
	T y;

	/// <summary>
	/// new Vectortor (0,0)
	/// </summary>
	TVector2(void) : x(), y()
	{ }

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="source">The source.</param>
	TVector2(const TVector2 &source)
	{
		Init(source.x, source.y);
	}



	/// <summary>
	/// new Vector (value,value)
	/// </summary>
	/// <param name="value">The value.</param>
	TVector2(T value) : x(value), y(value)
	{
		Init(value);
	}

	/// <summary>
	/// new Vector (x,y)
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	TVector2(T x, T y)
	{
		Init(x, y);
	}

	TVector2(TVector2 &&other) : x(other.x), y(other.y)
	{
	}


	~TVector2(void) {}

	/// <summary>
	/// component-wise minimum
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	static void Min(const TVector2& a, const TVector2& b, TVector2& out)
	{
		out.x = min(a.x, b.x);
		out.y = min(a.y, b.y);
	}

	/// <summary>
	/// Return the component-wise minimum of the operands
	/// </summary>
	static TVector2 Min(const TVector2& a, const TVector2& b)
	{
		TVector2 result;

		Min(a, b, result);

		return result;
	}


	/// <summary>
	/// component-wise maximum 
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	static void Max(const TVector2& a, const TVector2& b, TVector2& out)
	{
		out.x = max(a.x, b.x);
		out.y = max(a.y, b.y);
	}

	/// <summary>
	/// Return the component-wise maximum of the operands
	/// </summary>
	static TVector2 Max(const TVector2& a, const TVector2& b)
	{
		TVector2 result;

		Max(a, b, result);

		return result;
	}



	/// <summary>
	/// average (midpoint) of two Vectortors
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	static void Average(const TVector2 &a, const TVector2& b, TVector2& out)
	{
		out.x = (a.x + b.x) / 2;
		out.y = (a.y + b.y) / 2;
	}

	/// <summary>
	/// average (midpoint) of two Vectortors
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <returns>new Vectortor of the result</returns>
	static TVector2& Average(const TVector2& a, const TVector2& b)
	{
		TVector2 result;

		Average(a, b, result);

		return result;
	}

	static float Dot(const TVector2& left, const TVector2& right)
	{
		return left.x * right.x + left.y * right.y;
	}


	TVector2 operator+(const TVector2& right) const
	{
		return Vector2(this->x + right.x, this->y + right.y);
	}

	TVector2 operator*(const TVector2& multiplier) const
	{
		return Vector2(this->x * multiplier.x, this->y * multiplier.y);
	}

	TVector2 operator*(const float multiplier) const
	{
		return TVector2(this->x * multiplier, this->y * multiplier);
	}

	TVector2 operator/(const float divisor) const
	{
		float multiplier = 1.0f / divisor;
		return Vector2(this->x * multiplier, this->y * multiplier);
	}

	TVector2 operator/(const TVector2& divisor) const
	{
		return Vector2(this->x / divisor.x, this->y / divisor.y);
	}

	TVector2 &operator=(const TVector2& copyFrom)
	{
		x = copyFrom.x;
		y = copyFrom.y;

		return *this;
	}

	template<typename T2>
	TVector2 &operator=(const T2 &right)
	{
		x = right.x;
		y = right.y;

		return *this;
	}


	bool operator ==(T componentValue)
	{
		return x == componentValue && y == componentValue;
	}

	bool operator !=(T componentValue)
	{
		return x != componentValue || y != componentValue;
	}

	bool operator !=(const TVector2 &right)
	{
		return x != right.x || y != right.y;
	}

	std::string ToString()
	{
		return to_string(x) + "," + to_string(y);
	}

protected:

	/// <summary>
	/// Initialize the Vectortor
	/// </summary>
	/// <param name="x">Initial X value</param>
	/// <param name="y">Initial Y value</param>
	void Init(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	/// <summary>
	/// Initialize the Vectortor
	/// </summary>
	/// <param name="val">initial value for both X and Y</param>
	void Init(T val)
	{
		Init(val, val);
	}

};

/// <summary>
/// generic three-component Vectortor
/// </summary>
template<typename T = GLfloat>
class TVector3 : public TVector2<T>
{
public:
	T z;
	static const T Zero;

	/// <summary>
	/// new Vectortor (,0,0)
	/// </summary>
	TVector3(void) : z()
	{
	}

	/// <summary>
	/// new Vectortor(val,val,val)
	/// </summary>
	/// <param name="value">The value.</param>
	TVector3(T value)
	{
		Init(value);
	}

	/// <summary>
	/// new Vectortor (x,y,z)
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="z">The z.</param>
	TVector3(T x, T y, T z)
	{
		Init(x, y, z);
	}

	/// <summary>
	/// copy ctor
	/// </summary>
	/// <param name="source">The source.</param>
	TVector3(const TVector3 &source) : TVector2<T>(source)
	{
		z = source.z;
	}

	~TVector3(void) {}

	const static TVector3 &UnitY()
	{
		static TVector3 m_unitY(0, 1, 0);

		return m_unitY;
	}

	const static TVector3 &UnitX()
	{
		static TVector3 m_unitX(1, 0, 0);

		return m_unitX;
	}

	static float Length(const TVector3& v)
	{
		return sqrt(LengthSquared(v));
	}

	static float LengthSquared(const TVector3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;

	}

	float Length() const
	{
		return Length(*this);
	}

	float LengthSquared() const
	{
		return LengthSquared(*this);
	}

	void Normalize()
	{
		*this /= Length();
	}

	/// <summary>
	/// Component-wise Vectortor subtraction
	/// </summary>
	/// <param name="other">right side of operator</param>
	/// <returns></returns>
	TVector3 operator-(const TVector3& other) const
	{
		return TVector3(
			this->x - other.x
			, this->y - other.y
			, this->z - other.z
			);
	}

	/// <summary>
	/// Component-wise Vectortor addition
	/// </summary>
	/// <param name="other">right side of operator</param>
	/// <returns></returns>
	TVector3 operator+(const TVector3& other) const
	{
		return TVector3(
			this->x + other.x
			, this->y + other.y
			, this->z + other.z
			);
	}

	bool operator==(const TVector3 &other)
	{
		const float epsilon = numeric_limits<float>::epsilon();

		return abs(other.x - this->x) < epsilon
			&& abs(other.y - this->y) < epsilon
			&& abs(other.z - this->z) < epsilon
			;
	}

	/// <summary>
	/// Component-wise increment 
	/// </summary>
	/// <param name="other">The other.</param>
	void operator +=(const TVector3& other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
	}

	void operator -=(const TVector3 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
	}

	/// <summary>
	/// Component-wise multiplication
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
	TVector3 operator*(const TVector3& other) const
	{
		return TVector3(
			this->x*other.x
			, this->y*other.z
			, this->z*other.z
			);
	}

	TVector3 operator*(const float other) const
	{
		return TVector3(this->x * other, this->y * other, this->z * other);
	}

	void operator *=(const TVector3& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
	}

	void operator *=(const float other)
	{
		this->x *= other;
		this->y *= other;
		this->z *= other;
	}

	TVector3 operator /(const float other)
	{
		return *this * (1.0f / other);
	}

	void operator /=(const float other)
	{
		*this *= (1.0f / other);
	}


	/// <summary>
	/// Return the component-wise minimum of the operands
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	static void Min(const TVector3& a, const TVector3& b, TVector3& out)
	{
		TVector2<T>::Min(a, b, out);
		out.z = min(a.z, b.z);
	}

	/// <summary>
	/// Return the component-wise minimum of the operands
	/// </summary>
	static TVector3 Min(const TVector3& a, const TVector3& b)
	{
		TVector3 result;

		Min(a, b, result);

		return result;
	}

	/// <summary>
	/// Return the component-wise maximum of the operands
	/// </summary>
	static void Max(const TVector3& a, const TVector3& b, TVector3& out)
	{
		TVector2<T>::Max(a, b, out);
		out.z = max(a.z, b.z);
	}

	/// <summary>
	/// Return the component-wise maximum of the operands
	/// </summary>
	static TVector3 Max(const TVector3& a, const TVector3& b)
	{
		TVector3 result;

		Max(a, b, result);

		return result;
	}


	/// <summary>
	/// average (midpoint) of two Vectortors
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	static void Average(const TVector3& a, const TVector3& b, TVector3& out)
	{
		TVector2<T>::Average(a, b, out);
		out.z = (a.z + b.z) / 2.0f;
	}

	/// <summary>
	/// average (midpoint) of two Vectortors
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	static TVector3 Average(const TVector3& a, const TVector3& b)
	{
		TVector3 result;

		Average(a, b, result);

		return result;
	}

	static TVector3 m_identity;

	/// <summary>
	/// Returns a vector with all components set to 1.
	/// </summary>
	/// <returns></returns>
	static TVector3 One() {
		return m_identity;
	}

	static void Cross(const TVector3& left, const TVector3 right, TVector3& out)
	{
		out.z = left.x * right.y - left.y * right.x;
		out.x = left.y * right.z - left.z * right.y;
		out.y = left.z * right.x - left.x * right.z;
	}

	static TVector3 Cross(const TVector3& left, const TVector3& right)
	{
		TVector3 result;

		Cross(left, right, result);

		return result;
	}

	static float Dot(const TVector3& left, const TVector3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}



	static TVector3 Normalize(const TVector3& source)
	{
		TVector3 result = source;

		float inverseLength = 1.0f / Length(source);

		result.x *= inverseLength;
		result.y *= inverseLength;
		result.z *= inverseLength;

		return result;
	}
#define SWIZZLE2(left,right) TVector2<T> left ## right() { return TVector2<T>(left,right); }

//	SWIZZLE2(x, y)
//		SWIZZLE2(x, z)
//		SWIZZLE2(y, x)
//		SWIZZLE2(y, z)
//		SWIZZLE2(z, x)
//		SWIZZLE2(z, y)


protected:
	/// <summary>
	/// new Vectortor (val,val,val)
	/// </summary>
	/// <param name="val">The value.</param>
	void Init(T val)
	{
		TVector2<T>::Init(val);
		this->z = val;
	}

	/// <summary>
	/// new Vectortor (x,y,z)
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="z">The z.</param>
	void Init(T x, T y, T z)
	{
		TVector2<T>::Init(x, y);
		this->z = z;
	}





};

/// <summary>
/// generic 4-component Vectortor
/// </summary>
template<typename T = GLfloat>
class TVector4 : public TVector3<T>
{
protected:
	/// <summary>
	/// Initialize the Vectortor (val,val,val,val)
	/// </summary>
	/// <param name="val">initial value</param>
	void Init(T val)
	{
		TVector3<T>::Init(val);
		this->w = val;
	}

	/// <summary>
	/// initialize the Vectortor (x,y,z,w)
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="z">The z.</param>
	/// <param name="w">The w.</param>
	void Init(T x, T y, T z, T w)
	{
		TVector3<T>::Init(x, y, z);
		this->w = w;
	}
public:
	T w;

	/// <summary>
	/// new Vector4 (0,0,0,0)
	/// </summary>
	TVector4() : w()
	{
	}

	/// <summary>
	/// copy constructor
	/// </summary>
	/// <param name="source">The source.</param>
	TVector4(const TVector4 &source) : TVector3<T>(source)
	{
		w = source.w;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="TVector4{T}"/> class (value,value,value,value)
	/// </summary>
	/// <param name="value">The value.</param>
	TVector4(T value)
	{
		Init(value);
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="TVector4{T}"/> class.
	/// (x,y,z,w)
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="z">The z.</param>
	/// <param name="w">The w.</param>
	TVector4(T x, T y, T z, T w)
	{
		Init(x, y, z, w);
	}

	TVector4(TVector3<T> xyz, T w)
	{
		Init(xyz.x, xyz.y, xyz.z, w);
	}

	~TVector4()  { }


	/// <summary>
	/// find the component-wise minimum of the operands
	/// </summary>
	/// <param name="a">Vectortor</param>
	/// <param name="b">Vectortor</param>
	/// <param name="out">result</param>
	/// <returns></returns>
	static void Min(const TVector4& a, const TVector4& b, TVector4& out)
	{
		TVector3<T>::Min(a, b, out);
		out.w = min(a.w, b.w);
	}

	/// <summary>
	/// Return the component-wise minimum of the operands
	/// </summary>
	static TVector4 Min(const TVector4& a, const TVector4& b)
	{
		TVector4 result;

		Min(a, b, result);

		return result;
	}


	static TVector4<T> Max(const TVector4<T>& a, const TVector4<T>& b, TVector4<T>& out)
	{
		TVector3<T>::Max(a, b, out);
		out.w = max(a.w, b.w);
	}

	/// <summary>
	/// Return the component-wise maximum of the operands
	/// </summary>
	static TVector4 Max(const TVector4& a, const TVector4& b)
	{
		TVector4 result;

		Max(a, b, result);

		return result;
	}
}
;
#pragma endregion

#pragma region convience typedefs for float-based Vectortors.

typedef TVector2<GLfloat> Vector2;
typedef TVector3<GLfloat> Vector3;
typedef TVector4<GLfloat> Vector4;


#pragma endregion


#endif