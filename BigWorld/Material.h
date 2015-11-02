#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "GameObject.h"


class Material : public GameObject
{
public:
	Material(const std::string& name) : GameObject(name)
	{

	}

	Material() : Material("unknown.material")
	{

	}

private:

};

#endif