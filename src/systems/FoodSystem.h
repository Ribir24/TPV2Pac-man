// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;

class FoodSystem : public ecs::System {
public:

	FoodSystem();
	virtual ~FoodSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message&) override;
private:
	int _fils, _cols;
};

