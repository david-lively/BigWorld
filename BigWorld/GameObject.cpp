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

void GameObject::Update(const GameTime& time)
{
	DoPendingOperations();

	OnPreUpdate(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->OnPreUpdate(time);
	}

	OnUpdate(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->Update(time);
	}

	OnPostUpdate(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->OnPostUpdate(time);
	}

}

void GameObject::Render(const GameTime& time)
{
	OnPreRender(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->OnPreRender(time);
	}


	OnRender(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->Render(time);
	}

	OnPostRender(time);

	for (auto it = begin(Children); it != end(Children); ++it)
	{
		if (nullptr != *it)
			(*it)->OnPostRender(time);
	}

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