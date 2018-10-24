#ifndef LIGHT_H
#define LIGHT_H

#include <string>

#include "GameObject.h"
#include "Vectors.h"

class Light : GameObject
{
public:
    Light(const std::string& name) : GameObject(name), AmbientColor(Vector4(1,1,1,1)), SpecularColor(Vector4(1,1,1,1)), DiffuseColor(Vector4(1,1,1,1)))
    {
    
    }
    
    Light() : Light("unknown.light")
    {
        
    }
    
    Vector4 AmbientColor;
    Vector4 DiffuseColor;
    Vector4 SpecularColor;
    float Specularity;
    
private:
    

};



#endif
