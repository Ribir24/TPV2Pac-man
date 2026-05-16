// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Resistant : public ecs::Component {

	Resistant() :
		_T(0)
	{
	}
	~Resistant() {}
	int _T;
};

