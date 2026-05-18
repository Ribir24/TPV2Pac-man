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
	void cloneGhost(ecs::entity_t ghost);

	int _maxGhost;
	float _spawnTimer, _spawnInterval;

	Uint32 _lastTick;
};