#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

#include "Helper.h"
#include "Window.h"


class Graphics : public Helper
{
public:
	Graphics(const std::string& name) : Helper(name)
	{

	}
	Graphics() : Graphics("unknown.graphics")
	{

	}

	~Graphics()
	{

	}

	void AttachToWindow(Window& window)
	{
		m_window = &window;
	}
	
private:
	Window* m_window = nullptr;

};

#endif

