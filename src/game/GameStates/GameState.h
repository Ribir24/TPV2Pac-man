#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h> 
#include "../../ecs/messages.h"

class GameState {
public:
	GameState() {}
	virtual ~GameState() {}
	virtual void enter() = 0;
	virtual void leave() = 0;
	virtual void update() = 0;
};

