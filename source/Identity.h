#ifndef IDENTITY_H
#define IDENTITY_H

#include <iostream>
#include <string>
#include <functional>

#include "Common.h"


class Identity
{
public:
	Identity(const std::string& name)
	{
		m_name = name;
	}

	Identity(const Identity& toCopy)
	{
		m_id = toCopy.m_id;
		m_name = toCopy.m_name;
	}

	Identity()
	{
		m_id = ++m_nextId;

		m_name = "identity_" + std::to_string(m_id);
	}

	virtual ~Identity()
	{

	}

	int Id() const { return m_id; } 

	std::string& Name() { return m_name; } 

	void SetName(const std::string& name) { m_name = name; }


private:
	int m_id = 0;
	std::string m_name;

	static int m_nextId;

};



#endif