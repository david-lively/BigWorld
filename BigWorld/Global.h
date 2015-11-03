#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#include <typeinfo>
#include <string>
#include <map>
#include <vector>

#include "Log.h"
#include "Vectors.h"
#include "Matrix4.h"

#define DECLARE_SET_UNIFORM(T) \
template<>                 \
T& SetUniform<T>(const std::string& name, const T& value)


namespace Global
{
    
    template<typename T>
    T& SetUniform(const std::string& name, const T& value)
    {
        Log::Error << "Unhandled uniform type\n";
        throw;
    }
    
    DECLARE_SET_UNIFORM(Matrix4);
    DECLARE_SET_UNIFORM(Vector4);
    DECLARE_SET_UNIFORM(Vector3);
    DECLARE_SET_UNIFORM(Vector2);
    DECLARE_SET_UNIFORM(float);
    DECLARE_SET_UNIFORM(int);
    
    /// set all global uniforms for the current program
    int ApplyAll();
    
    /// initialize the list of active uniforms for the given program.
    void InitializeUniformMap(GLuint program);
    
}

#undef DECLARE_SET_UNIFORM


#endif