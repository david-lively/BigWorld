#include <stdexcept>
#include <cmath>
#include <memory>
#include "Vectors.h"
#include "Math.h"
#include "Matrix4.h"

using namespace Math;

shared_ptr<Matrix4> Matrix4::m_identity;
Matrix4::m_init Matrix4::m_initializer;

void Matrix4::Initialize()
{
	m_identity = std::make_shared<Matrix4>(
		Matrix4(1, 0, 0, 0
		, 0, 1, 0, 0
		, 0, 0, 1, 0
		, 0, 0, 0, 1
		));
}


void Matrix4::Transpose(Matrix4& matrix)
{
	throw runtime_error("Not implemented");
}

void Matrix4::CreateTranslation(float x, float y, float z, Matrix4& m)
{
	m = Identity();

	m.row3.x = x;
	m.row3.y = y;
	m.row3.z = z;


}

void Matrix4::CreateTranslation(const Vector3& translation, Matrix4& m)
{
	CreateTranslation(translation.x, translation.y, translation.z, m);

	m.UpdateOrientationVectors();
}



/// <summary>
/// Creates a translation matrix
/// </summary>
/// <param name="x">x offset</param>
/// <param name="y">y offset</param>
/// <param name="z">z offset</param>
/// <returns></returns>
Matrix4 Matrix4::CreateTranslation(float x, float y, float z)
{
	Matrix4 m;

	CreateTranslation(x, y, z, m);

	return m;
}




/// <summary>
/// Builds a matrix for a rotation around the x-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <param name="m">The resulting Matrix4 instance.</param>
void Matrix4::CreateRotationX(float angle, Matrix4& m)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);

	m.row1.y = cos;
	m.row1.z = sin;
	m.row2.y = -sin;
	m.row2.z = cos;

	m.UpdateOrientationVectors();

}


/// <summary>
/// Builds a matrix for a rotation around the x-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <returns>a rotation matrix</returns>
Matrix4 Matrix4::CreateRotationX(float angle)
{
	Matrix4 m;

	CreateRotationX(angle, m);

	return m;
}


/// <summary>
/// Builds a rotation matrix for a rotation around the Y-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <param name="m">The resulting Matrix4 instance.</param>
void Matrix4::CreateRotationY(float angle, Matrix4& m)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);

	m.row0.x = cos;
	m.row0.z = sin;
	m.row2.x = -sin;
	m.row2.z = cos;

	m.UpdateOrientationVectors();
}

/// <summary>
/// Builds a rotation matrix for a rotation around the Y-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <returns>a rotation matrix</returns>
Matrix4 Matrix4::CreateRotationY(float angle)
{
	Matrix4 m;

	CreateRotationY(angle, m);

	return m;
}


/// <summary>
/// Builds a rotation matrix for a rotation around the z-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <param name="m">The resulting Matrix4 instance.</param>
void Matrix4::CreateRotationZ(float angle, Matrix4& m)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);

	m.row0.x = cos;
	m.row0.y = sin;
	m.row1.x = -sin;
	m.row1.y = cos;

	m.UpdateOrientationVectors();
}

/// <summary>
/// Builds a rotation matrix for a rotation around the z-axis.
/// </summary>
/// <param name="angle">The counter-clockwise angle in radians.</param>
/// <returns>a rotation matrix</returns>
Matrix4 Matrix4::CreateRotationZ(float angle)
{
	Matrix4 result;

	CreateRotationZ(angle, result);

	return result;
}

/// <summary>
/// Creates a rotation matrix that rotates angles.* radians around the respective axis.
/// </summary>
/// <param name="angles">The angles.</param>
/// <param name="m">The m.</param>
void Matrix4::CreateRotation(const Vector3 &radians, Matrix4& m)
{
	float xa = radians.x;
	float ya = radians.y;
	float za = radians.z;

	float cx = std::cos(xa);
	float sx = std::sin(xa);

	float cy = std::cos(ya);
	float sy = std::sin(ya);

	float cz = std::cos(za);
	float sz = std::sin(za);


	// see http://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/MARBLE/high/pose/express.htm
	/*
	cos(ay)cos(az)		sin(ax)sin(ay)cos(az) - cos(ax)sin(az)		cos(ax)sin(ay)cos(az) + sin(ax)sin(az)
	cos(ay)sin(az)		sin(ax)sin(ay)sin(az) + cos(ax)cos(az)		cos(ax)sin(ay)sin(az) - sin(ax)cos(az)
	-sin(ay)			sin(ax)cos(ay)								cos(ax)cos(ay)
	*/

	m = Matrix4(
		cy*cz, sx*sy*cz - cx*cz, cx*sy*cz + sx*sz, 0
		,
		cy*sz, sx*sy*sz + cx*cz, cx*sy*sz - sx*cz, 0
		,
		-sy, sx*cy, cx*cy, 0
		,
		0, 0, 0, 1
		);

	m.UpdateOrientationVectors();
}



/// <summary>
/// Build a single 4x4 matrix containing scaling, rotation and translation operations
/// </summary>
/// <param name="scale">The scale.</param>
/// <param name="rotate">The rotate.</param>
/// <param name="translate">The translate.</param>
/// <param name="out">The out.</param>
void Matrix4::CreateScaleRotateTranslate(
	const Vector3& scale
	, const Vector3& rotate
	, const Vector3& translate
	, Matrix4& m
	)
{
	CreateScaleRotateTranslate(m, scale.x, scale.y, scale.z, rotate.x, rotate.y, rotate.z, translate.x, translate.y, translate.z);
	m.UpdateOrientationVectors();
}

void Matrix4::CreateScaleRotateTranslate(
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
	)
{
	throw runtime_error("Not implemented");
}


/// <summary>
/// Creates a matrix that scales all components of a Vectortor by the given value
/// </summary>
/// <param name="scaleBy">Scalar applied to all components of a multiplicand Vectortor</param>
/// <returns>scaling matrix</returns>
Matrix4 Matrix4::CreateScale(float scaleBy)
{
	Matrix4 m;

	CreateScale(scaleBy, m);

	return m;
}

void Matrix4::CreateScale(float scaleBy, Matrix4& m)
{
	m.row0.x = scaleBy;
	m.row1.y = scaleBy;
	m.row2.z = scaleBy;
	m.row3.w = 1;
	m.UpdateOrientationVectors();
}

void Matrix4::CreateScale(const Vector3& scale, Matrix4 &m)
{
	m = Identity();

	m.row0.x = scale.x;
	m.row1.y = scale.y;
	m.row2.z = scale.z;

	m.UpdateOrientationVectors();
}

Matrix4 Matrix4::CreateScale(const Vector3& scale)
{
	Matrix4 m;
	CreateScale(scale, m);
	return m;
}


void Matrix4::Scale(Matrix4& m, const Vector3& scaleBy)
{
	auto lm00 = scaleBy.x;
	auto lm11 = scaleBy.y;
	auto lm22 = scaleBy.z;
	auto lm33 = 1;

	auto right = m;
	float
		//float lm00 = left.row0.x, lm01 = left.row0.y, lm02 = left.row0.z, lm03 = left.row0.w,
		//	lm10 = left.row0.x, lm11 = left.row0.y, lm12 = left.row0.z, lm13 = left.row0.w,
		//	lm20 = left.row1.x, lm21 = left.row1.y, lm22 = left.row1.z, lm23 = left.row1.w,
		//	lm30 = left.row2.x, lm31 = left.row2.y, lm32 = left.row2.z, lm33 = left.row2.w,
		rm00 = right.row0.x, rm01 = right.row0.y, rm02 = right.row0.z, rm03 = right.row0.w,
		rm10 = right.row1.x, rm11 = right.row1.y, rm12 = right.row1.z, rm13 = right.row1.w,
		rm20 = right.row2.x, rm21 = right.row2.y, rm22 = right.row2.z, rm23 = right.row2.w,
		rm30 = right.row3.x, rm31 = right.row3.y, rm32 = right.row3.z, rm33 = right.row3.w;

	m.row0.x = lm00 * rm00;
	m.row0.y = lm00 * rm01;
	m.row0.z = lm00 * rm02;
	m.row0.w = lm00 * rm03;

	m.row1.x = lm11 * rm10;
	m.row1.y = lm11 * rm11;
	m.row1.z = lm11 * rm12;
	m.row1.w = lm11 * rm13;

	m.row2.x = lm22 * rm20;
	m.row2.y = lm22 * rm21;
	m.row2.z = lm22 * rm22;
	m.row2.w = lm22 * rm23;

	m.row3.x = lm33 * rm30;
	m.row3.y = lm33 * rm31;
	m.row3.z = lm33 * rm32;
	m.row3.w = lm33 * rm33;

	m.UpdateOrientationVectors();
}



/// <summary>
/// multiply a Vectortor by the given matrix
/// </summary>
/// <param name="m">transform matrix</param>
/// <param name="v">source Vectortor</param>
/// <returns>transformed Vectortor</returns>
Vector3 Matrix4::Transform(Matrix4& m, Vector3& v)
{
	Vector3 result;

	result.x = dot(m.row0, v);
	result.y = dot(m.row1, v);
	result.z = dot(m.row2, v);

	return result;
}

/// <summary>
/// multiply a Vectortor by the given matrix
/// </summary>
/// <param name="m">transform matrix</param>
/// <param name="v">source Vectortor</param>
/// <returns>transformed Vectortor</returns>
Vector4 Matrix4::Transform(Matrix4& m, Vector4& v)
{
	Vector4 result;

	result.x = dot(m.row0, v);
	result.y = dot(m.row1, v);
	result.z = dot(m.row2, v);
	result.w = dot(m.row3, v);

	return result;

}


Vector4 Matrix4::Transform(const Vector4& v)
{
	Vector4 result = v;

	result = Matrix4::Transform(*this, result);

	return result;
}



/// <summary>
/// Create a perspective projection matrix using some standard values
/// </summary>
/// <param name="matrix">The matrix.</param>
void Matrix4::CreatePerspectiveFieldOfView(Matrix4& matrix)
{
	CreatePerspectiveFieldOfView(
		Math::PI / 4.0f
		, 1280.0f / 720
		, 1.0f
		, 100000.0f
		, matrix
		);
}


/// <summary>
/// Create a perspective projection matrix using some standard values
/// </summary>
Matrix4 Matrix4::CreatePerspectiveFieldOfView()
{
	Matrix4 result;

	CreatePerspectiveFieldOfView(result);

	return result;
}


Matrix4 Matrix4::InverseProjection(const Matrix4& projection)
{

	float a = projection.row0.x;
	float b = projection.row1.y;
	float c = projection.row2.z;
	float d = projection.row2.w;
	float e = projection.row3.z;

	Matrix4 inverse;

	inverse.row0.x = 1.f / a;
	inverse.row1.y = 1.f / b;
	inverse.row2.w = 1.f / e;

	inverse.row3.z = 1.f / d;
	inverse.row3.w = -c / (d * e);

	return inverse;


}


/// <summary>
/// Create an off-center perspective projection matrix
/// </summary>
/// <param name="left">The left.</param>
/// <param name="right">The right.</param>
/// <param name="bottom">The bottom.</param>
/// <param name="top">The top.</param>
/// <param name="zNear">The z near.</param>
/// <param name="zFar">The z far.</param>
/// <param name="result">The result.</param>
/// <returns></returns>
/// <remarks>Shamelessly stolen from OpenTK.Matrix4 class</remarks>
void Matrix4::CreatePerspectiveOffCenter(
	float left
	, float right
	, float bottom
	, float top
	, float zNear
	, float zFar
	, Matrix4 &result
	)
{
	if (zNear <= 0)
		throw out_of_range("Near plane cannot be negative");
	if (zFar <= 0)
		throw new out_of_range("Far plane must be greater than the near plane");
	if (zNear >= zFar)
		throw new out_of_range("Near plane must be closer than the far plane");

	float x = (2.0f * zNear) / (right - left);
	float y = (2.0f * zNear) / (top - bottom);
	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(zFar + zNear) / (zFar - zNear);
	float d = -(2.0f * zFar * zNear) / (zFar - zNear);

	result.row0 = Vector4(x, 0, 0, 0);
	result.row1 = Vector4(0, y, 0, 0);
	result.row2 = Vector4(a, b, c, -1);
	result.row3 = Vector4(0, 0, d, 0);

	//result.row0.x = x;
	//result.row0.y = 0;
	//result.row0.z = 0;
	//result.row0.w = 0;

	//result.row1.x = 0;
	//result.row1.y = y;
	//result.row1.z = 0;
	//result.row1.w = 0;

	//result.row2.x = a;
	//result.row2.y = b;
	//result.row2.z = c;
	//result.row2.w = -1;

	//result.row3.x = 0;
	//result.row3.y = 0;
	//result.row3.z = d;
	//result.row3.w = 0;

	result.UpdateOrientationVectors();
}


/// <summary>
/// Creates the a projection matrix
/// </summary>
/// <param name="fieldOfView">The field of view.</param>
/// <param name="aspectRatio">The aspect ratio.</param>
/// <param name="zNear">near clip plane</param>
/// <param name="zFar">far clip plane</param>
/// <param name="matrix">resulting projection matrix</param>
void Matrix4::CreatePerspectiveFieldOfView(
	float fieldOfView
	, float aspectRatio
	, float zNear
	, float zFar
	, Matrix4 &matrix
	)
{
	if (fieldOfView <= 0 || fieldOfView > Math::PI)
		throw out_of_range("Field of view must be between > 0 and <= PI");

	if (aspectRatio <= 0)
		throw out_of_range("Aspect ratio must be positive");

	if (zNear <= 0)
		throw out_of_range("Near clip plane must be >= 0");

	if (zFar <= 0 || zFar <= zNear)
		throw out_of_range("Far clipping plane must be positive, and greater than near clipping plane.");

	float yMax = zNear * std::tan(0.5f * fieldOfView);
	float yMin = -yMax;
	float xMin = yMin * aspectRatio;
	float xMax = yMax * aspectRatio;

	CreatePerspectiveOffCenter(xMin, xMax, yMin, yMax, zNear, zFar, matrix);
}


/// <summary>
/// returns a projection matrix
/// </summary>
/// <param name="fieldOfView">The field of view.</param>
/// <param name="aspectRatio">The aspect ratio.</param>
/// <param name="zNear">The z near.</param>
/// <param name="zFar">The z far.</param>
/// <returns>a projection matrix</returns>
Matrix4 Matrix4::CreatePerspectiveFieldOfView(
	float fieldOfView
	, float aspectRatio
	, float zNear
	, float zFar
	)
{
	Matrix4 result;

	CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, zNear, zFar, result);

	return result;
}



/// <summary>
/// Multiplies two instances.
/// </summary>
/// <param name="left">The left operand of the multiplication.</param>
/// <param name="right">The right operand of the multiplication.</param>
/// <param name="result">A new instance that is the result of the multiplication.</param>
void Matrix4::Mult(const Matrix4& left, const Matrix4& right, Matrix4& result)
{
	/// borrowed from OpenTK
	float lm11 = left.row0.x, lm12 = left.row0.y, lm13 = left.row0.z, lm14 = left.row0.w,
		lm21 = left.row1.x, lm22 = left.row1.y, lm23 = left.row1.z, lm24 = left.row1.w,
		lm31 = left.row2.x, lm32 = left.row2.y, lm33 = left.row2.z, lm34 = left.row2.w,
		lm41 = left.row3.x, lm42 = left.row3.y, lm43 = left.row3.z, lm44 = left.row3.w,
		rm11 = right.row0.x, rm12 = right.row0.y, rm13 = right.row0.z, rm14 = right.row0.w,
		rm21 = right.row1.x, rm22 = right.row1.y, rm23 = right.row1.z, rm24 = right.row1.w,
		rm31 = right.row2.x, rm32 = right.row2.y, rm33 = right.row2.z, rm34 = right.row2.w,
		rm41 = right.row3.x, rm42 = right.row3.y, rm43 = right.row3.z, rm44 = right.row3.w;

	result.row0.x = (((lm11 * rm11) + (lm12 * rm21)) + (lm13 * rm31)) + (lm14 * rm41);
	result.row0.y = (((lm11 * rm12) + (lm12 * rm22)) + (lm13 * rm32)) + (lm14 * rm42);
	result.row0.z = (((lm11 * rm13) + (lm12 * rm23)) + (lm13 * rm33)) + (lm14 * rm43);
	result.row0.w = (((lm11 * rm14) + (lm12 * rm24)) + (lm13 * rm34)) + (lm14 * rm44);
	result.row1.x = (((lm21 * rm11) + (lm22 * rm21)) + (lm23 * rm31)) + (lm24 * rm41);
	result.row1.y = (((lm21 * rm12) + (lm22 * rm22)) + (lm23 * rm32)) + (lm24 * rm42);
	result.row1.z = (((lm21 * rm13) + (lm22 * rm23)) + (lm23 * rm33)) + (lm24 * rm43);
	result.row1.w = (((lm21 * rm14) + (lm22 * rm24)) + (lm23 * rm34)) + (lm24 * rm44);
	result.row2.x = (((lm31 * rm11) + (lm32 * rm21)) + (lm33 * rm31)) + (lm34 * rm41);
	result.row2.y = (((lm31 * rm12) + (lm32 * rm22)) + (lm33 * rm32)) + (lm34 * rm42);
	result.row2.z = (((lm31 * rm13) + (lm32 * rm23)) + (lm33 * rm33)) + (lm34 * rm43);
	result.row2.w = (((lm31 * rm14) + (lm32 * rm24)) + (lm33 * rm34)) + (lm34 * rm44);
	result.row3.x = (((lm41 * rm11) + (lm42 * rm21)) + (lm43 * rm31)) + (lm44 * rm41);
	result.row3.y = (((lm41 * rm12) + (lm42 * rm22)) + (lm43 * rm32)) + (lm44 * rm42);
	result.row3.z = (((lm41 * rm13) + (lm42 * rm23)) + (lm43 * rm33)) + (lm44 * rm43);
	result.row3.w = (((lm41 * rm14) + (lm42 * rm24)) + (lm43 * rm34)) + (lm44 * rm44);

	result.UpdateOrientationVectors();
}



/// <summary>
/// Transposes this instance.
/// </summary>
void Matrix4::Transpose()
{
	*this = Matrix4(col0(), col1(), col2(), col3());

	UpdateOrientationVectors();

}



void Matrix4::CreateFromQuaternion(const Vector4& quaternion, Matrix4 &m)
{
	float num9 = quaternion.x * quaternion.x;
	float num8 = quaternion.y * quaternion.y;
	float num7 = quaternion.z * quaternion.z;
	float num6 = quaternion.x * quaternion.y;
	float num5 = quaternion.z * quaternion.w;
	float num4 = quaternion.z * quaternion.x;
	float num3 = quaternion.y * quaternion.w;
	float num2 = quaternion.y * quaternion.z;
	float num = quaternion.x * quaternion.w;
	m.row0.x = 1.0f - (2.0f * (num8 + num7));
	m.row0.y = 2.0f * (num6 + num5);
	m.row0.z = 2.0f * (num4 - num3);
	m.row0.w = 0.0f;
	m.row1.x = 2.0f * (num6 - num5);
	m.row1.y = 1.0f - (2.0f * (num7 + num9));
	m.row1.z = 2.0f * (num2 + num);
	m.row1.w = 0.0f;
	m.row2.x = 2.0f * (num4 + num3);
	m.row2.y = 2.0f * (num2 - num);
	m.row2.z = 1.0f - (2.0f * (num8 + num9));
	m.row2.w = 0.0f;
	m.row3.x = 0.0f;
	m.row3.y = 0.0f;
	m.row3.z = 0.0f;
	m.row3.w = 1.0f;

	m.UpdateOrientationVectors();

}

void Matrix4::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Vector4& quaternion)
{
	float num9 = roll * 0.5f;
	float num6 = (float)sin((double)num9);
	float num5 = (float)cos((double)num9);
	float num8 = pitch * 0.5f;
	float num4 = (float)sin((double)num8);
	float num3 = (float)cos((double)num8);
	float num7 = yaw * 0.5f;
	float num2 = (float)sin((double)num7);
	float num = (float)cos((double)num7);

	quaternion.x = ((num * num4) * num5) + ((num2 * num3) * num6);
	quaternion.y = ((num2 * num3) * num5) - ((num * num4) * num6);
	quaternion.z = ((num * num3) * num6) - ((num2 * num4) * num5);
	quaternion.w = ((num * num3) * num5) + ((num2 * num4) * num6);



}

void Matrix4::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix4& m)
{
	Vector4 q;
	CreateFromYawPitchRoll(yaw, pitch, roll, q);
	CreateFromQuaternion(q, m);
}

void Matrix4::CreateFromYawPitchRoll(const Vector3& radians, Matrix4& m)
{
	CreateFromYawPitchRoll(radians.x, radians.y, radians.z, m);

	m.UpdateOrientationVectors();

}

/// <summary>
/// Build a world space to camera space matrix
/// </summary>
/// <param name="eye">Eye (camera) position in world space</param>
/// <param name="target">Target position in world space</param>
/// <param name="up">Up vector in world space (should not be parallel to the camera direction, that is target - eye)</param>
/// <returns>A Matrix4 that transforms world space to camera space</returns>
void Matrix4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& out)
{
	Vector3 z = Vector3::Normalize(eye - target);
	Vector3 x = Vector3::Normalize(Vector3::Cross(up, z));
	Vector3 y = Vector3::Normalize(Vector3::Cross(z, x));

	out.row0.x = x.x;
	out.row0.y = y.x;
	out.row0.z = z.x;
	out.row0.w = 0;
	out.row1.x = x.y;
	out.row1.y = y.y;
	out.row1.z = z.y;
	out.row1.w = 0;
	out.row2.x = x.z;
	out.row2.y = y.z;
	out.row2.z = z.z;
	out.row2.w = 0;
	out.row3.x = -((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z));
	out.row3.y = -((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z));
	out.row3.z = -((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z));
	out.row3.w = 1;

	out.UpdateOrientationVectors();
}

void Matrix4::UpdateOrientationVectors(void)
{
	m_up = Vector3(row1.x, row1.y, row1.z);
	m_down = Vector3(-row1.x, -row1.y, -row1.z);
	m_left = Vector3(-row0.x, -row0.y, -row0.z);
	m_right = Vector3(row0.x, row0.y, row0.z);
	m_forward = Vector3(-row2.x, -row2.y, -row2.z);
	m_backward = Vector3(row2.x, row2.y, row2.z);


	//m.row0.x=cos;
	//m.row0.z=sin;
	//m.row2.x=-sin;
	//m.row2.z=cos;

	m_north.x = row2.x;
	m_north.y = 0;
	m_north.z = -row2.z;

	m_south = m_north * -1;
	/// x= -y, y = x
	m_east.x = -m_north.z;
	m_east.y = 0;
	m_east.z = m_north.x;

	m_west = m_east * -1;
}


#pragma region CreateOrthographic

/// <summary>
/// Creates an orthographic projection matrix.
/// </summary>
/// <param name="width">The width of the projection volume.</param>
/// <param name="height">The height of the projection volume.</param>
/// <param name="zNear">The near edge of the projection volume.</param>
/// <param name="zFar">The far edge of the projection volume.</param>
/// <param name="result">The resulting Matrix4 instance.</param>
void Matrix4::CreateOrthographic(float width, float height, float zNear, float zFar, Matrix4 &result)
{
	CreateOrthographicOffCenter(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar, result);
}

/// <summary>
/// Creates an orthographic projection matrix.
/// </summary>
/// <param name="width">The width of the projection volume.</param>
/// <param name="height">The height of the projection volume.</param>
/// <param name="zNear">The near edge of the projection volume.</param>
/// <param name="zFar">The far edge of the projection volume.</param>
/// <rereturns>The resulting Matrix4 instance.</rereturns>
Matrix4 Matrix4::CreateOrthographic(float width, float height, float zNear, float zFar)
{
	Matrix4 result;

	CreateOrthographicOffCenter(-width / 2, width / 2, -height / 2, height / 2, zNear, zFar, result);

	return result;
}

#pragma endregion

#pragma region CreateOrthographicOffCenter

/// <summary>
/// Creates an orthographic projection matrix.
/// </summary>
/// <param name="left">The left edge of the projection volume.</param>
/// <param name="right">The right edge of the projection volume.</param>
/// <param name="bottom">The bottom edge of the projection volume.</param>
/// <param name="top">The top edge of the projection volume.</param>
/// <param name="zNear">The near edge of the projection volume.</param>
/// <param name="zFar">The far edge of the projection volume.</param>
/// <param name="result">The resulting Matrix4 instance.</param>
void Matrix4::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4 &result)
{

	float invRL = 1 / (right - left);
	float invTB = 1 / (top - bottom);
	float invFN = 1 / (zFar - zNear);

	result = Matrix4(
		2 * invRL, 0, 0, 0
		,
		0, 2 * invTB, 0, 0
		,
		0, 0, -2 * invFN, 0
		,
		-(right + left) * invRL, -(top + bottom) * invTB, -(zFar + zNear) * invFN, 1
		);

	/*
	result.M00 = 2 * invRL;
	result.M11 = 2 * invTB;
	result.M22 = -2 * invFN;

	result.M30 = -(right + left) * invRL;
	result.M31 = -(top + bottom) * invTB;
	result.M32 = -(zFar + zNear) * invFN;
	result.M33 = 1;
	*/
}

/// <summary>
/// Creates an orthographic projection matrix.
/// </summary>
/// <param name="left">The left edge of the projection volume.</param>
/// <param name="right">The right edge of the projection volume.</param>
/// <param name="bottom">The bottom edge of the projection volume.</param>
/// <param name="top">The top edge of the projection volume.</param>
/// <param name="zNear">The near edge of the projection volume.</param>
/// <param name="zFar">The far edge of the projection volume.</param>
/// <returns>The resulting Matrix4 instance.</returns>
Matrix4 Matrix4::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNear, float zFar)
{
	Matrix4 result;
	CreateOrthographicOffCenter(left, right, bottom, top, zNear, zFar, result);
	return result;
}

#pragma endregion

