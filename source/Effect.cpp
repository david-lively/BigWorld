#include <string>
#include <array>
#include <map>

#include "Effect.h"

#include "Common.h"
#include "ResourceManager.h"
#include "Files.h"
#include "Log.h"
#include "Enums.h"
#include "Shader.h"
#include "Global.h"

using namespace std;

void Effect::EnsureCreated()
{
	if (Handle != 0)
		return;

	Build(PathBase);
//	BuildVAO();

	Resource::EnsureCreated();
}


void Effect::OnRender(const GameTime& time)
{
	EnsureCreated();

	Bind();

	SetUniforms(time);
}


bool Effect::Build(const string& resourceName)
{
	static const map<string, ShaderType> extensions =
	{
		{ ".vert", ShaderType::VertexShader }
		, { ".geom", ShaderType::GeometryShader }
		, { ".frag", ShaderType::FragmentShader }
		, { ".tessc", ShaderType::TessControlShader }
		, { ".tesse", ShaderType::TessEvaluationShader }
		, { ".comp", ShaderType::ComputeShader }
	};


	Handle = gl::CreateProgram();

	int shaderCount = 0;

	m_shaders.clear();

	for (auto it = begin(extensions); it != end(extensions); ++it)
	{
		string path = resourceName + it->first + ".glsl";
        
        Log::Info <<  "Looking for shader \"" + path + "\"...";
        
		if (!Files::Exists(path))
        {
            Log::Info << Log::NoHeader << " - NOT FOUND\n";
            continue;
        }
        else
        {
            Log::Info << Log::NoHeader << " found, loading\n";
        }

		auto& shader = ResourceManager::Instance->Create<Shader>(path);

		bool succeeded = false;


		while(!succeeded)
		{
			auto source = Files::Read(path);
			succeeded = shader.Build(it->second, source);

			if (!succeeded)
			{
				Log::Error << "Error compiling \"" << path << "\"\n" << shader.Log << endl;
				cout << "Shader compilation error. Press enter to retry." << endl;
				getchar();
			}
			else
				Log::Info << "Building shader \"" << path << "\"" << endl;
		}


		m_shaders[it->second] = shader;

		gl::AttachShader(Handle, shader.Handle);

		++shaderCount;

	}


	if (0 == shaderCount)
	{
		Log::Error << "No shaders found for effect \"" << resourceName << "\"" << endl;
		return false;
	}

	gl::LinkProgram(Handle);

	Log = GetLog();

	if (Log.length() > 0)
	{
        bool isFatal = Log.find("ERROR") < Log.length();
        
        if (isFatal)
        {
            Log::Error << "FATAL Program errors for \"" <<  resourceName << "\"\n";
            Log::Error << Log << endl;

            return false;
        }
        else
        {
            Log::Warning << "Warnings for program \"" <<  resourceName << "\"\n";
            Log::Warning << Log::NoHeader << Log << endl;
        }
        
	}
    
    Global::InitializeUniformMap(Handle);

	return true;
}


/// <summary>
/// Gets the program information log.
/// </summary>
/// <param name="program">The program.</param>
/// <returns></returns>
std::string Effect::GetLog()
{
	string log = "";
	GLint logLength = 0;

	/// this is useless.
	GLint returnedLength;

	gl::GetProgramiv(Handle, gl::INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		char* logBuffer = new char[logLength + 1];

		gl::GetProgramInfoLog(Handle, logLength, &returnedLength, logBuffer);

		log = string(logBuffer);

		delete logBuffer;
	}

	return log;
}

void Effect::SetUniform(const std::string& name, const Matrix4& value)
{
    
}

void Effect::SetUniform(const std::string& name, const Vector4& value)
{
    
}

void Effect::SetUniform(const std::string& name, const Vector3& value)
{
    
}

void Effect::SetUniform(const std::string& name, const Vector2& value)
{
    
}

void Effect::SetUniform(const std::string& name, const float& value)
{
    
}

void Effect::SetUniform(const std::string& name, const int& value)
{
    
}




