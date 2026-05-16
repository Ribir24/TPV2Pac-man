// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include <SDL.h> 

class RiskSystem: public ecs::System {
public:

	RiskSystem();
	virtual ~RiskSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;

private:
	float _distance = 50.0f;
	int _timeToAct = 2000;
	bool _act = false, _imm = false;
	int _duration = 5000;
	int _count = 0;
	Uint32 _lastTick;
};