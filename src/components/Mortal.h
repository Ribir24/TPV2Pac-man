// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Mortal : public ecs::Component {

	Mortal() :
		_T(), _pos(), _V()
	{
	}
	~Mortal() {}


	int _T, _V;
	Vector2D _pos;
};

