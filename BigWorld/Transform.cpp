#include "Transform.h"
#include "Matrix4.h"

Matrix4& Transform::GetScaleMatrix()
{
	if (m_scaleIsDirty)
	{
		Matrix4::CreateScale(m_scale, m_scaleMatrix);
		m_scaleIsDirty = false;
	}

	return m_scaleMatrix;
}

Matrix4& Transform::GetRotationMatrix()
{
	if (m_rotationIsDirty)
	{
		Matrix4::CreateFromYawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z, m_rotationMatrix);
		m_rotationIsDirty = false;
	}

	return m_rotationMatrix;
}

Matrix4& Transform::GetTranslationMatrix()
{
	if (m_translationIsDirty)
	{
		Matrix4::CreateTranslation(m_translation, m_translationMatrix);
		m_translationIsDirty = false;
	}

	return m_translationMatrix;
}

bool Transform::IsDirty()
{
	return m_worldIsDirty | (nullptr != m_parent ? m_parent->IsDirty() : false);
}

Matrix4& Transform::GetWorldMatrix()
{
	if (IsDirty())
	{
		m_worldMatrix = GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();

		if (m_parent)
			m_worldMatrix = m_worldMatrix * m_parent->GetWorldMatrix();

		m_worldIsDirty = false;
		UpdateOrientationVectors();
	}
	return m_worldMatrix;
}