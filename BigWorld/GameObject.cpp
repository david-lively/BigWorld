#include <algorithm>

#include "GameObject.h"
#include "Log.h"
#include "Window.h"

using namespace std;

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	if (nullptr != Parent)
		Parent->Delete(this);

}

void GameObject::DoPendingOperations()
{
	for (int i = (int)ToDelete.size() - 1; i >= 0; --i)
	{
		GameObject* item = ToDelete[i];

		Children.erase(std::remove(Children.begin(), Children.end(), item), Children.end());
	}

	ToDelete.clear();
}

void GameObject::DoPreUpdate(const GameTime& time)
{
    OnPreUpdate(time);
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPreUpdate(time);
    }
    
}

void GameObject::DoUpdate(const GameTime& time)
{
    OnUpdate(time);
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoUpdate(time);
    }
    
}

void GameObject::DoPostUpdate(const GameTime& time)
{
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPostUpdate(time);
    }

    OnPostUpdate(time);
    
}

void GameObject::DoPreRender(const GameTime& time)
{
    OnPreRender(time);
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPreRender(time);
    }
    
}

void GameObject::DoRender(const GameTime& time)
{
    OnRender(time);
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoRender(time);
    }
    
}

void GameObject::DoPostRender(const GameTime& time)
{
    
    for (auto it = begin(Children); it != end(Children); ++it)
    {
        if (nullptr != *it)
            (*it)->DoPostRender(time);
    }

    OnPostRender(time);
    
}




void GameObject::Update(const GameTime& time)
{
	DoPendingOperations();
    
    DoPreUpdate(time);
    DoUpdate(time);
    DoPostUpdate(time);
}

void GameObject::Render(const GameTime& time)
{
 
    Log::Info << "GameObject::Render \"" << Name() << "\"\n";
    
    DoPreRender(time);
    DoRender(time);
    DoPostRender(time);
}

void GameObject::Delete(GameObject* item)
{
	if (nullptr == item)
		return;

	ToDelete.push_back(item);	
}

void GameObject::Load()
{
	Log::Info << "Loading \"" << Name() << "\"\n";

	OnLoad();

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		(*it)->Load();
	}

}

void GameObject::Initialize()
{
	Log::Info << "Initializing \"" << Name() << "\"\n";

	OnInitialize();

	for (auto it = begin(Children); it != end(Children); ++it)
		(*it)->Initialize();

}