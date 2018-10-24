#ifndef BUFFER_H
#define	BUFFER_H

#include <string>
#include <vector>

#include "Resource.h"
#include "Enums.h"


template<typename T>
class Buffer : public Resource
{
public:
	BufferTarget    Target = BufferTarget::ArrayBuffer;
	BufferUsageHint Usage = BufferUsageHint::StaticDraw;

	Buffer(const std::string& name) : Resource(name)
	{

	}

	Buffer() : Resource("unnamed-buffer")
	{

	}

	void Bind() override
	{
		if (Handle == 0)
			return;

		gl::BindBuffer((GLenum)Target, Handle);
	}

	void Unbind() override
	{ 
		if (Handle == 0)
			return;

		gl::BindBuffer((GLenum)Target, 0);
	}

	void Release() override
	{
		if (Handle == 0)
			return;

		gl::DeleteBuffers(1, &Handle);
	}

	void EnsureCreated() override
	{
		if (Handle != 0)
			return;

		gl::GenBuffers(1, &Handle);
	}

	
	template<typename ForwardIterator>
	void SetData(ForwardIterator head, ForwardIterator tail, bool leaveBound = false)
	{
        if (tail-head <= 0)
        {
            Log::Error << "Buffer cannot contain zero elements\n";
            throw;
        }
        
        m_data.resize(tail-head);
        std::copy(head, tail, begin(m_data));
        
        check_gl_error();

		EnsureCreated();

		check_gl_error();
        
        auto bytes = m_data.size() * sizeof(m_data[0]);
        
        Log::Info << "Initializing buffer with " << m_data.size() << " elements (" << bytes << " bytes)\n";

		Bind();

		check_gl_error();

		gl::BufferData((GLenum)Target, bytes, m_data.data(), (GLenum)Usage);

		check_gl_error();

		if (!leaveBound)
			Unbind();

		check_gl_error();
	}

	template<typename TCollection>
	void SetData(const TCollection& data, bool leaveBound = false)
	{
		SetData(std::begin(data), std::end(data), leaveBound);
	}

    /// number of elements in the buffer
	const size_t Count() const
	{
        return m_data.size();
	}
    
    /// data
    std::vector<T>& Data()
    {
        return m_data;
    }

private:
    /// buffer data that was sent to OpenGL
    std::vector<T> m_data;
};



#endif