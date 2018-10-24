#ifndef GAME_H
#define GAME_H

#include <vector>
#include <set>

#include "Common.h"
#include "Graphics.h"
#include "ResourceManager.h"

class Game : public GameObject
{
public:
	Game();
	~Game();

	/// useful for GLFW callbacks.
	static Game* Instance;

	int Run();

	ResourceManager Resources;
};




#endif



