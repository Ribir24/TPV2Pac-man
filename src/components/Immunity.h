// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Immunity : public ecs::Component {

	Immunity() :
		_active(false)
	{}
	~Immunity() {}
	bool _active;
};

