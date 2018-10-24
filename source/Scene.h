#ifndef SCENE_H
#define SCENE_H

#include <string>

#include "GameObject.h"


class Scene : public GameObject
{
public:
    Scene(const std::string& name) : GameObject(name)
    {
    
    }
private:
    
};



#endif