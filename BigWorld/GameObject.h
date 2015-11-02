#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Common.h"
#include "Identity.h"
#include "GameComponent.h"
#include "ResourceManager.h"

#include <vector>

/// <summary>
/// A potentially renderable, updatable object
/// </summary>
class GameObject : public Identity
{
	friend class Game;
public:
	GameObject();
	GameObject(const std::string& name) : Identity(name)
	{

	}

	~GameObject();

	GameObject* Parent = nullptr;
	std::vector<GameObject*> Children;
	std::vector<GameComponent*> Components;

	virtual void OnPreUpdate(const GameTime&) {}
	virtual void OnUpdate(const GameTime&) {}
	virtual void OnPostUpdate(const GameTime&) {}
	
	void Update(const GameTime&);

	virtual void OnPreRender(const GameTime&) {}
	virtual void OnRender(const GameTime&) {}
	virtual void OnPostRender(const GameTime&) {}

	void Render(const GameTime&);

	virtual void OnLoad() {};
	virtual void OnInitialize() {};


	template<typename T>
	T& Create(const std::string& name)
	{
		T& item = ResourceManager::Instance->Create<T>(name);

		Children.push_back(&item);

		return item;
	}

	template<typename T>
	T& Get(const std::string& name)
	{
		return ResourceManager::Instance->Get<T>(name);
	}

	void Delete(GameObject* item);

protected:
	std::vector<GameObject*> ToDelete;

private:
	void Load();
	void Initialize();
	
	void DoPendingOperations();

};



#endif