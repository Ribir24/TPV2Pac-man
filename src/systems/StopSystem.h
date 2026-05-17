// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include <SDL.h> 

struct Transform;

class StopSystem : public ecs::System {
public:

	StopSystem();
	virtual ~StopSystem();
	void initSystem() override;
	void update() override;
private:

	float _stopTimer, _stopInterval, _stopDuration;
	bool _active;

	Uint32 _lastTick;
};