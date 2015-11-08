#include "Console.h"
#include "GameObject.h"
#include "Effect.h"

#include <string>
#include <vector>

using namespace std;



void Console::OnLoad()
{
    GameObject::OnLoad();
    
    /// load up effects and any other assets reqzired for console rendering.
    
    auto& effect = Create<Effect>("console");

    effect.Rebuild();
    effect.Bind();
    
    Global::InitializeUniformMap(effect.Handle);
    
    
    string x = "Hello Console!";
    m_vertexArray.SetData(x);
    
}


void Console::OnRender(const GameTime& time)
{
    GameObject::OnRender(time);
}



