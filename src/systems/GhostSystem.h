// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include <SDL.h> 

struct Transform;

class GhostSystem : public ecs::System {
public:

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;
private:
	void spawnGhost();
	int _maxGhost;
	float _spawnTimer, _spawnInterval;

	const int Ni = 1; const int Nd = 5;
	const int Mi = 1000; const int Md = 10000;
	const float P = 10; 

	Uint32 _lastTick;
};