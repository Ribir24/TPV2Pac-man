// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

struct Type : public ecs::Component {

	Type() 
	{}
	~Type() {}
	int _type;
};

