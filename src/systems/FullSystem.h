// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/SDLUtils.h"
#include <vector>
#include <SDL.h> 

struct Transform;

class FullSystem : public ecs::System {
public:

	FullSystem();
	virtual ~FullSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;

private:
	bool _active;
	std::vector<int> _foodEaten;
	int _fullDuration, _interval;
	int _amountToFull;
	int _timer;

	Uint32 _lastTick;
};

