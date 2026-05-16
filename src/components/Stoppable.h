// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Stoppable : public ecs::Component {

	Stoppable() :
		_stopped(false)
	{
	}
	~Stoppable() {}
	bool _stopped;
};

