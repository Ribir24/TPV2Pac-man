// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 
#include "../utils/Vector2D.h"

struct Clone : public ecs::Component {

	Clone()
	{}
	~Clone() {}
	
	ecs::entity_t _original;
	Vector2D _speed;
};

