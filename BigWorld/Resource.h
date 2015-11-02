#ifndef RESOURCE_H
#define	RESOURCE_H

#include <string>

#include "GameObject.h"

class Resource : public GameObject
{
public:
	GLuint Handle = 0;

	Resource(const std::string& name) : GameObject(name)
	{
	}


	virtual ~Resource()	{

	}

	virtual void Create() {}

	virtual void Bind()
    {
        EnsureCreated();
    }

	virtual void Unbind() {}

	virtual void EnsureCreated() {}

	virtual void Release() {}

private:
};


#endif