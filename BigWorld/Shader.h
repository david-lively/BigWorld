#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "Resource.h"
#include "Enums.h"


class Shader : public Resource
{
public:
	std::string Log;
	ShaderType Type;
	std::string PathBase;

	Shader(const std::string& name) : Resource(name)
	{

	}

	Shader() : Shader("shader.unknown")
	{

	}

	~Shader()
	{
		if (Handle > 0)
		{
			gl::DeleteShader(Handle);
			Handle = 0;
		}
	}

	void EnsureCreated() override;
	
	bool Build(ShaderType type, const std::string& source);
	std::string GetLog(GLuint shader);


private:

};


#endif
