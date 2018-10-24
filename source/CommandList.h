#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "GameObject.h"
#include "Command.h"

#include <vector>

/// list of Commands that are executed in the given order. 
class CommandList : public GameObject
{
public:
	CommandList();
	~CommandList();

	/// commands attached to this object for drawing, setting GL state, etc.
	std::vector<Command*> Commands;
};

#endif

