#ifndef EFFECT_H
#define EFFECT_H

#include <string>
#include <map>

#include "Enums.h"
#include "Resource.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Global.h"

/// 
class Effect : public Resource
{
public:
	std::string PathBase;
	std::string Log;

	Effect(const std::string& name) : Resource(name)
	{
		PathBase = name;
	}

	Effect() : Effect("unknown.effect")
	{

	}

	void EnsureCreated() override;

	bool Build(const std::string& resourceName);
    
    
	void Rebuild()
	{
		check_gl_error();

		Build(PathBase);

		check_gl_error();
	}

	std::string GetLog();

	/// bind effect and set uniforms
	void OnRender(const GameTime& time);

	virtual void SetUniforms(const GameTime&)
	{
        Global::ApplyAll();

	}

	void Bind() override
	{
        EnsureCreated();
        
		gl::UseProgram(Handle);
	}
    
    void SetUniform(const std::string& name, const Matrix4& value);
    void SetUniform(const std::string& name, const Vector4& value);
    void SetUniform(const std::string& name, const Vector3& value);
    void SetUniform(const std::string& name, const Vector2& value);
    void SetUniform(const std::string& name, const float& value);
    void SetUniform(const std::string& name, const int& value);


private:
	std::map<ShaderType, Shader> m_shaders;
    std::map<std::string,GLint> m_uniformLocations;

};

#endif