#ifndef MESH_H
#define MESH_H

#include <string>

#include "GameObject.h"
#include "Buffer.h"
#include "Enums.h"
#include "Vertex.h"
#include "VertexArray.h"


template<typename TVertex = VertexPositionColor, typename TIndex = int>
class Mesh : public Resource
{
public:
	Mesh(const std::string& name) : Resource(name)
	{
//		m_vertexBuffer.Usage = BufferUsageHint::StaticDraw;
//		m_vertexBuffer.Target = BufferTarget::ArrayBuffer;

		m_indexBuffer.Usage = BufferUsageHint::StaticDraw;
		m_indexBuffer.Target = BufferTarget::ElementArrayBuffer;
	}

	Mesh() : Mesh("mesh.unknown")
	{
	}

	BeginMode Type = BeginMode::Triangles;

	template<typename TVertices, typename TIndices>
	void SetData(TVertices& vertices, TIndices& indices)
	{
        m_vertexArray.SetData(vertices);

		if (indices.size() > 0)
			m_indexBuffer.SetData(indices);
	}

	void OnRender(const GameTime& time) override
	{
        Log::Info << "Drawing \"" << Name() << "\"\n";
        check_gl_error();
        
		Bind();

        check_gl_error();

        if (m_indexBuffer.Count() > 0)
			gl::DrawElements((GLenum)Type, (GLsizei)m_indexBuffer.Count(), (GLenum)ElementType::UnsignedInt, 0);
		else
            gl::DrawArrays((GLenum)Type, 0, (GLsizei)m_vertexArray.VertexBuffer().Count());

		check_gl_error();
	}

	void Bind() override
	{
		check_gl_error();
        
        m_vertexArray.Bind();

		check_gl_error();
		
		m_indexBuffer.Bind();
		
		check_gl_error();

	}

	void Unbind() override
	{
        m_vertexArray.Unbind();
		m_indexBuffer.Unbind();
	}

	void Release() override
	{
        m_vertexArray.Release();
		m_indexBuffer.Release();
	}

private:
	Buffer<TIndex> m_indexBuffer;
    VertexArray<TVertex> m_vertexArray;

};


#endif