#include "Game.h"
#include "Graphics.h"
#include "Common.h"
#include "GameTime.h"
#include "Log.h"

#include <iostream>
#include <vector>

using namespace std;

Game* Game::Instance = nullptr;

Game::Game()
{
	if (nullptr != Game::Instance)
		throw runtime_error("Only one game instance is allowed.");

	Game::Instance = this;
}

Game::~Game()
{
}


int Game::Run()
{
	Load();

	Initialize();

	while (Children.size() > 0)
	{		
		auto& time = GameTime::Current().Update();

		Update(time);
		Render(time);
	}

	glfwTerminate();

	return 0;
}

