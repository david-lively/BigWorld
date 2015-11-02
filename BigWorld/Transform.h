#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <set>

#include "Common.h"
#include "GameComponent.h"
#include "Vectors.h"
#include "Matrix4.h"

class Transform : public GameComponent
{

public:

	Transform(const std::string& name)
	{
		m_scale = Vector3(1);
		m_worldIsDirty = true;
		m_rotationIsDirty = true;
		m_translationIsDirty = true;
		m_scaleIsDirty = true;
		m_parent = nullptr;
	}


	void Scale(float value)
	{
		m_scale.x = m_scale.y = m_scale.z = value;
	}

	void Scale(float x, float y, float z)
	{
		m_scale.x = x;
		m_scale.y = y;
		m_scale.z = z;
	}

	void Scale(const Vector3& scale)
	{
		m_scale = scale;
		m_scaleIsDirty = true;
		m_worldIsDirty = true;
	}

	void ScaleBy(const Vector3 &scale)
	{
		m_scale *= scale;
		m_scaleIsDirty = true;
		m_worldIsDirty = true;
	}

	const Vector3& Scale() const { return m_scale; }

	virtual void Rotate(const Vector3& radians)
	{
		m_rotation = radians;
		m_rotationIsDirty = true;
		m_worldIsDirty = true;
	}

	virtual void RotateBy(const Vector3& radians)
	{
		m_rotation += radians;
		m_rotationIsDirty = true;
		m_worldIsDirty = true;
	}

	const Vector3& Rotation() const { return m_rotation; }

	virtual void Translate(const Vector3& translation)
	{
		m_translation = translation;
		m_translationIsDirty = true;
		m_worldIsDirty = true;
	}

	virtual void Translate(float x, float y, float z)
	{
		m_translation.x = x;
		m_translation.y = y;
		m_translation.z = z;
		m_translationIsDirty = true;
		m_worldIsDirty = true;
	}

	virtual void TranslateBy(const Vector3& moveBy)
	{
		m_translation += moveBy;
		m_translationIsDirty = true;
		m_worldIsDirty = true;
	}

	Matrix4& GetScaleMatrix();
	Matrix4& GetRotationMatrix();
	Matrix4& GetTranslationMatrix();
	Matrix4& GetWorldMatrix();


	/// set the transform's parent, and update relevant transform children collections.
	void SetParent(Transform *newParent)
	{
		if (m_parent != newParent)
		{
			if (nullptr != m_parent)
			{
				m_parent->m_children.erase(this);
			}
			m_parent = newParent;

			if (nullptr != m_parent)
			{
				m_parent->m_children.insert(this);
			}
		}
	}

	bool IsDirty();

#pragma region navigation and camera convenience helpers

	const Vector3 &Forward() const { return m_rotationMatrix.m_forward; }

	const Vector3 &Backward() const { return m_rotationMatrix.m_backward; }

	const Vector3 &Up() const { return m_rotationMatrix.m_up; }

	const Vector3 &Down() const { return m_rotationMatrix.m_down; }

	const Vector3 &Right() const { return m_rotationMatrix.m_right; }

	const Vector3 &Left() const { return m_rotationMatrix.m_left; }

	const Vector3 &Translation() const { return m_translation; }

	const Vector3 &North() const { return m_rotationMatrix.m_north; }

	const Vector3 &East() const { return m_rotationMatrix.m_east; }

	void UpdateOrientationVectors()
	{
		m_rotationMatrix.UpdateOrientationVectors();
	}

#pragma endregion

private:

	Vector3 m_scale;
	bool m_scaleIsDirty;
	Matrix4 m_scaleMatrix;

	Vector3 m_rotation;
	bool m_rotationIsDirty;
	Matrix4 m_rotationMatrix;


	Vector3 m_translation;
	bool m_translationIsDirty;
	Matrix4 m_translationMatrix;

	bool m_worldIsDirty;
	Matrix4 m_worldMatrix;

	set<Transform*> m_children;
	Transform *m_parent;
};

#endif