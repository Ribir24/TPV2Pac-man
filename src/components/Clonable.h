// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Clonable : public ecs::Component {

	Clonable() :
		_N(20000)
	{
	}
	~Clonable() {}
	int _N;
};

