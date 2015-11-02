#include "BigWorldGame.h"

#include "Common.h"
#include "Log.h"
#include "MenuScreen.h"


BigWorldGame::BigWorldGame()
{
	SetName("BigWorldGame");
}


BigWorldGame::~BigWorldGame()
{
}

void BigWorldGame::OnLoad()
{
	auto& mainWindow = Create<Window>("MainWindow");
	
	auto& screen = mainWindow.Create<MenuScreen>("MenuScreen");
}

