#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <iostream>

#include "GameObject.h"
#include "Log.h"
#include "ResourceManager.h"
#include "Graphics.h"
#include "Effect.h"

class MenuScreen : public GameObject
{
public:
	MenuScreen();

	MenuScreen(const std::string& name) : GameObject(name)
	{
	}

	~MenuScreen();

	void OnLoad() override;
//	void OnInitialize() override;
	void OnRender(const GameTime& time) override;

	void CreateScene();

private:
	GameObject* m_quad = nullptr;
	Effect* m_effect = nullptr;

};

#endif

