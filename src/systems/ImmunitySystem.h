// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/SDLUtils.h"

struct Transform;

class ImmunitySystem : public ecs::System {
public:

	ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;

private:
	bool _active;
	Uint32 _startTime;
};

