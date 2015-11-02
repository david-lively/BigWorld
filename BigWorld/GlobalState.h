#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#include <typeinfo>
#include <string>
#include <map>

#include "Log.h"
#include "Vectors.h"
#include "Matrix4.h"

class GlobalState
{
public:
    GlobalState()
    {
        if (nullptr != m_instance)
        {
            Log::Error << "Only one instance of class Global is allowed.\n";
            throw;
        }
        
        m_instance = this;
    }
    
    ~GlobalState()
    {
        m_instance = nullptr;
    }
    
    void SetUniform(const std::string& name, const Matrix4& value);
    void SetUniform(const std::string& name, const Vector4& value);
    void SetUniform(const std::string& name, const Vector3& value);
    void SetUniform(const std::string& name, const Vector2& value);
    void SetUniform(const std::string& name, const float& value);
    void SetUniform(const std::string& name, const int& value);
    
private:
    GlobalState* m_instance = nullptr;
    
    std::map<std::string,Matrix4> m_uniformMatrices;

};

#endif