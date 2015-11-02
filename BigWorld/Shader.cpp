#include "Shader.h"
#include "Log.h"

#include <string>

using namespace std;

void Shader::EnsureCreated()
{
	if (0 != Handle)
		return;



}


bool Shader::Build(const ShaderType type, const string& source)
{
	if (0 != Handle)
	{
		Log::Info << "Deleting shader \"" << Name() << "\"";
		gl::DeleteShader(Handle);
	}

	Handle = gl::CreateShader((GLenum)type);

	if (0 == Handle)
		Log::Error << "OpenGL could not create shader!";

	GLint len = (GLint)source.length();
	GLchar* src = (GLchar*)source.c_str();

	gl::ShaderSource(Handle, 1, &src, &len);
	gl::CompileShader(Handle);

	Log = GetLog(Handle);

	return Log.length() == 0;
}


/// <summary>
/// Gets the shader information log.
/// </summary>
/// <param name="shader">The shader.</param>
/// <returns></returns>
std::string Shader::GetLog(GLuint shader)
{
	string log = "";
	GLint logLength = 0;


	gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &logLength);

	if (logLength > 0)
	{
		char *logBuffer = new char[logLength];

		/// this is useless when using std::string
		GLint returnedLength;

		gl::GetShaderInfoLog(shader, logLength, &returnedLength, logBuffer);
		log = string(logBuffer);

		delete logBuffer;
	}


	/*
	strip any leading digits, which make the error message incompatible with Visual Studio
	*/
	auto firstParen = log.find("(");
	if (firstParen != string::npos && firstParen > 0)
	{
		log = log.substr(firstParen, string::npos);
	}

	return log;
}

