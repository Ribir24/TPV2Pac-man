// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Stopable : public ecs::Component {

	Stopable() :
		_stoped(false)
	{
	}
	~Stopable() {}
	bool _stoped;
};

