#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

#include "Vectors.h"

struct VertexField
{
	std::string Name;

	VertexField(const std::string& name)
	{
		Name = name;
	}

	virtual int Size() 
	{
		return -1;
	}
};

template<typename T>
struct TVertexField : public VertexField
{
	T Data;

	int Size() override
	{
		return sizeof(Data);
	}
};

template<typename T>
void BindVertexAttributes()
{
    throw;
}


class VertexType
{
public:
    std::vector<VertexField*> Fields;

	void Add(VertexField* field)
	{
		Fields.push_back(field);
		m_size += field->Size();
	}

	int Size()
	{
		return m_size;
	}
    
    

private:
	int m_size;
};


struct VertexPosition
{
	Vector3 Position;
};

inline GLint TryBindAttribute(const GLint programID, const std::string& name, GLint size = 4, GLenum type = gl::FLOAT, GLsizei stride = 12)
{
    auto location = gl::GetAttribLocation(programID, name.c_str());
    if (location < 0)
        return location;
    
    
    gl::EnableVertexAttribArray(location);
    gl::VertexAttribPointer(location, size, type, false, stride, nullptr);
    
    return location;
    
    
}

template<>
inline void BindVertexAttributes<VertexPosition>()
{
    GLint programId = -1;
    gl::GetIntegerv(gl::CURRENT_PROGRAM, &programId);
    
    TryBindAttribute(programId, "Position", 4, gl::FLOAT, sizeof(Vector3));
    
}

    
    
    
struct VertexPositionColor{
    
    Vector3 Position;
	Vector4 Color;
};

template<>
inline void BindVertexAttributes<VertexPositionColor>()
{
    auto stride = sizeof(Vector3) + sizeof(Vector4);
    gl::VertexAttribPointer(0, 3, gl::FLOAT, false, (GLsizei)stride, nullptr);
    gl::VertexAttribPointer(1, 4, gl::FLOAT, false, (GLsizei)stride, nullptr);
}

struct VertexChar
{
    char Char;
};

template<>
inline void BindVertexAttributes<char>()
{
    auto stride = sizeof(char);
    gl::VertexAttribPointer(0, 1, gl::BYTE, false,(GLsizei)stride, nullptr);
}


#endif