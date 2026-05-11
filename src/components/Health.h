// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Health : public ecs::Component {

	Health() :
		_lives(3)
	{
	}
	~Health() {}
	int _lives;
};

