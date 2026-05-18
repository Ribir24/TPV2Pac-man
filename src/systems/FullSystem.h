// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
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
	int _maxFruit;
	float _timer, _interval;

	bool _active;
	
	Uint32 _lastTick;
};