#ifndef MATRIX4_H
#define MATRIX4_H

#include <memory>
#include "Vectors.h"

class Transform;

/// <summary>
/// 4x4 matrix class. Note that operations must be performed in SRT (scale, rotate, translate) order, which is the opposite of OpenGL.
/// </summary>
class Matrix4
{
	friend class Transform;
public:
	static const Matrix4& Identity() { return *m_identity; }

	Vector4 row0;
	Vector4 row1;
	Vector4 row2;
	Vector4 row3;

	Vector4 col0() { return Vector4(row0.x, row1.x, row2.x, row3.x); }
	Vector4 col1() { return Vector4(row0.y, row1.y, row2.y, row3.y); }
	Vector4 col2() { return Vector4(row0.z, row1.z, row2.z, row3.z); }
	Vector4 col3() { return Vector4(row0.w, row1.w, row2.w, row3.w); }

	Matrix4()
	{
		*this = *m_identity;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="Matrix4"/> class.
	/// </summary>
	/// <param name="source">The source.</param>
	Matrix4(const Matrix4 &source)
	{
		row0 = source.row0;
		row1 = source.row1;
		row2 = source.row2;
		row3 = source.row3;
	}

	/// <summary>
	/// Initializes a new instance of the <see cref="Matrix4"/> class.
	/// </summary>
	Matrix4(
		float m00, float m10, float m20, float m30
		, float m01, float m11, float m21, float m31
		, float m02, float m12, float m22, float m32
		, float m03, float m13, float m23, float m33
		)
	{
		row0 = Vector4(m00, m10, m20, m30);
		row1 = Vector4(m01, m11, m21, m31);
		row2 = Vector4(m02, m12, m22, m32);
		row3 = Vector4(m03, m13, m23, m33);
	}

	Matrix4(
		const Vector4& row0
		, const Vector4& row1
		, const Vector4& row2
		, const Vector4& row3
		)
	{
		this->row0 = row0;
		this->row1 = row1;
		this->row2 = row2;
		this->row3 = row3;
	}

	~Matrix4()
	{
	}

	const Vector3& Up() const { return m_up; }
	const Vector3& Down() const { return m_down; }
	const Vector3& Left() const { return m_left; }
	const Vector3& Right() const { return m_right; }
	const Vector3& Forward() const { return m_forward; }
	const Vector3& Backward() const { return m_backward; }


	const Vector3 Translation() const { return Vector3(row0.x, row0.y, row0.z); }

	static void CreateFromQuaternion(const Vector4& quaternion, Matrix4 &m);

	static void CreateFromYawPitchRoll(const Vector3& radians, Matrix4& m);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix4& m);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Vector4& quaternion);


	static void Transpose(Matrix4& matrix);

	static void CreateTranslation(const Vector3& radians, Matrix4& m);
	static void CreateTranslation(float x, float y, float z, Matrix4& m);
	static Matrix4 CreateTranslation(float x, float y, float z);

	static Matrix4 CreateRotationX(float angle);
	static void CreateRotationX(float angle, Matrix4& m);

	static Matrix4 CreateRotationY(float angle);
	static void CreateRotationY(float angle, Matrix4& m);

	static Matrix4 CreateRotationZ(float angle);
	static void CreateRotationZ(float angle, Matrix4& m);

	static Matrix4 CreateScale(float scaleBy);

	static void CreateScale(float scaleBy, Matrix4& m);
	static void CreateScale(const Vector3& scale, Matrix4 &m);
	static Matrix4 CreateScale(const Vector3& scale);


	static void CreateIdentity(Matrix4 &m)
	{
		m = *m_identity;
	}


	static void Scale(Matrix4& m, const Vector3& scaleBy);

	static Vector3 Transform(Matrix4& m, Vector3& v);

	static Vector4 Transform(Matrix4& m, Vector4& v);
	Vector4 Transform(const Vector4& v);


	static Matrix4 CreatePerspectiveFieldOfView();
	static void CreatePerspectiveFieldOfView(Matrix4 &matrix);

	static void CreatePerspectiveFieldOfView(
		float fieldOfView
		, float aspectRatio
		, float zNear
		, float zFar
		, Matrix4 &matrix
		);

	static Matrix4 CreatePerspectiveFieldOfView(
		float fieldOfView
		, float aspectRatio
		, float zNear
		, float zFar
		);

	static void CreatePerspectiveOffCenter(
		float left
		, float right
		, float bottom
		, float top
		, float zNear
		, float zFar
		, Matrix4 &result
		);

	static Matrix4 InverseProjection(const Matrix4& projection);

	static void CreateOrthographic(float width, float height, float zNear, float zFar, Matrix4 &result);
	static Matrix4 CreateOrthographic(float width, float height, float zNear, float zFar);
	static void CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4 &result);
	static Matrix4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar);
	
	static void CreateRotation(const Vector3 &angles, Matrix4& m);

	static void CreateScaleRotateTranslate(const Vector3& scale, const Vector3& rotate, const Vector3& translate, Matrix4& m);
	static void CreateScaleRotateTranslate(
		Matrix4& m
		, float sx
		, float sy
		, float sz
		, float rx
		, float ry
		, float rz
		, float tx
		, float ty
		, float tz
		);

	static void LookAt(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& out);

	static void Mult(const Matrix4& left, const Matrix4& right, Matrix4& result);

	static Matrix4 Mult(const Matrix4& left, const Matrix4& right)
	{
		Matrix4 result;

		Mult(left, right, result);

		return result;
	}

	Matrix4 operator*(const Matrix4& right)
	{
		return Mult(*this, right);
	}

	void Transpose();
	void UpdateOrientationVectors();

private:
	static std::shared_ptr<Matrix4> m_identity;

	Vector3 m_up;
	Vector3 m_down;
	Vector3 m_left;
	Vector3 m_right;
	Vector3 m_forward;
	Vector3 m_backward;
	Vector3 m_north;
	Vector3 m_south;
	Vector3 m_east;
	Vector3 m_west;

	static void Initialize();

	static class m_init
	{
	public:
		m_init() {
			Initialize();
		}
	} m_initializer;

};


#endif
