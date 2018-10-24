#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <string>

#include "Vertex.h"
#include "Buffer.h"
#include "Resource.h"

class VertexArrayBase : public Resource
{
public:
	VertexArrayBase(const std::string& name) : Resource(name)
	{

	}

	VertexArrayBase() : VertexArrayBase("unknown.vertexarray")
	{

	}


    
    void EnsureCreated() override
    {
        if (0 != Handle)
            return;
        
        gl::GenVertexArrays(1, &Handle);
    }

private:

};

template<typename T>
class VertexArray : public VertexArrayBase
{
public:
	VertexArray(const std::string& name) : VertexArrayBase(name)
	{

	}

	VertexArray() : VertexArray("unknown.vertexarray")
	{

	}
    void EnsureCreated() override
    {
        if (0 != Handle)
            return;
        
        gl::GenVertexArrays(1, &Handle);
        gl::BindVertexArray(Handle);
        
        check_gl_error();
        
        VertexArrayBase::EnsureCreated();
        m_vertexBuffer.Bind();

        check_gl_error();
        
        BindVertexAttributes<T>();

        check_gl_error();

    }
    
    inline Buffer<T>& VertexBuffer()
    {
        return m_vertexBuffer;
    }
    
    template<typename TCollection>
    void SetData(TCollection& data)
    {
        m_vertexBuffer.SetData(data);
    
    }
    
   
    void Bind() override
    {
        Resource::Bind();
        
        gl::BindVertexArray(Handle);
        
    }
    
    void Unbind() override
    {
        gl::BindVertexArray(0);
    }
    
    void Release() override
    {
        gl::DeleteVertexArrays(1, &Handle);
    }
    
    
private:
    Buffer<T> m_vertexBuffer;
    
    

};




#endif