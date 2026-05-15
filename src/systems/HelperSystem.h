// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include <SDL.h> 

struct Transform;

class HelperSystem : public ecs::System {
public:

	HelperSystem();
	virtual ~HelperSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;
private:
	void spawnHelper();
	int _N;
	float _spawnTimer, _spawnInterval;

	//Mortal component
	int MinT, MaxT;
	int mortProb, _V;


	Uint32 _lastTick;
};