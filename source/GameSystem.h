#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include <ctime>

#include "Identity.h"

class GameSystem : public Identity
{
public:
	GameSystem()
	{

	}

	virtual ~GameSystem() = 0
	{

	}

	virtual void Update(std::time_t time)
	{

	}

private:

};




#endif