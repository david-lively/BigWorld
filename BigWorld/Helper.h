#ifndef HELPER_H
#define HELPER_H

#include "Common.h"
#include "Identity.h"

class Helper : public Identity
{
public:
	Helper(const std::string& name) : Identity(name)
	{

	}

	Helper() : Helper("helper.unknown")
	{

	}

	virtual ~Helper()
	{

	}

	void Attach(GLFWwindow* window)
	{
		m_window = window;
	}

	GLFWwindow* GetWindow()
	{
		return m_window;
	}


private:
	GLFWwindow* m_window = nullptr;

};


#endif