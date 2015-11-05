#include <map>
#include <string>
#include <vector>

using namespace std;

#include "Matrix4.h"
#include "Vectors.h"

#include "Global.h"

using namespace Global;

template<typename T>
int Apply()
{
    Log::Error << "Unsupported uniform type\n";
}

map<GLint, map<string,GLint>> m_uniformLocations;

GLint GetUniformLocation(GLint program, const string& name)
{
    auto v = m_uniformLocations[program].find(name);
    
    if (v == end(m_uniformLocations[program]))
        /// doesn't exist
        m_uniformLocations[program][name] = -1;
    
    return m_uniformLocations[program][name];
}


void Global::InitializeUniformMap(GLuint program)
{
    m_uniformLocations[program].clear();
    
    if(!gl::IsProgram(program))
    {
        Log::Warning << program << " is not a valid program name.\n";
        return;
    }
    
    check_gl_error();
    
    GLint prevProgram = 0;

    gl::GetIntegerv(gl::CURRENT_PROGRAM, &prevProgram);

    check_gl_error();
    
    GLsizei maxNameLength = 0;

    gl::GetProgramiv(program, gl::ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

    check_gl_error();
    
    char nameBuffer[maxNameLength + 1];
    
    GLint uniformCount = 0;
    
    gl::GetProgramiv(program, gl::ACTIVE_UNIFORMS, &uniformCount);
    
    check_gl_error();

    for(int i = 0; i < uniformCount; ++i)
    {
        GLenum type;
        GLsizei nameLength = 0;
        
        gl::GetActiveUniform(program, i, maxNameLength, &nameLength, nullptr, &type, nameBuffer);
        
        check_gl_error();

        if (nameLength == 0)
            continue;
        
        GLint location = gl::GetUniformLocation(program, nameBuffer);
        
        check_gl_error();

        if (location < 0)
            continue;
        
        m_uniformLocations[program][string(nameBuffer)] = location;
        
        Log::Info << "Found shader uniform " << location << " \"" << nameBuffer << "\"\n";
    }

    check_gl_error();
    
    gl::UseProgram(prevProgram);
    
    check_gl_error();
    
}


#define APPLY(T,GL_SUFFIX) \
template<> \
int Apply ## T<T>(GLint program) {                                      \
int count = 0;                                                      \
for(auto i = begin(m_uniform ## T); i != end(m_uniform ## T); ++i)  \
{                                                                   \
auto location = GetUniformLocation(program, i->first);          \
if (location >= 0) {                                            \
gl::Uniform ## GL_SUFFIX(program, i->second);               \
++count;                                                    \
}                                                               \
}                                                                   \
return count;                                                       \
}

#define SET_UNIFORM(T)                                                  \
std::map<std::string, T> m_uniform ## T;                                \
template<>                                                              \
T& Global::SetUniform<T>(const std::string& name, const T& value)       \
{                                                                       \
m_uniform ## T[name] = value;                                       \
return m_uniform ## T[name];                                        \
}                                                                       \


SET_UNIFORM(Matrix4)
SET_UNIFORM(Vector4)
SET_UNIFORM(Vector3)
SET_UNIFORM(Vector2)
SET_UNIFORM(float)
SET_UNIFORM(int)



int Global::ApplyAll()
{
    GLint programId = -1;
    
    gl::GetIntegerv(gl::CURRENT_PROGRAM, &programId);
    
    if (programId == 0)
    {
        Log::Error << "Global::Apply - No program is bound.\n";
        return 0;
    }
    
    {
        auto it = m_uniformLocations.find(programId);
    
        if (it == end(m_uniformLocations))
            InitializeUniformMap(programId);
    }
    
    auto& uniforms = m_uniformLocations[programId];
    
    for(auto it = begin(m_uniformMatrix4); it != end(m_uniformMatrix4); ++it)
    {
        auto ptr = uniforms.find(it->first);
        if (ptr != end(uniforms))
        {
            GLfloat* p= (GLfloat*)&(it->second);
            gl::UniformMatrix4fv(ptr->second, 1, false, p);
        }
    }
    
    
    
    
    return -1;
    
}




