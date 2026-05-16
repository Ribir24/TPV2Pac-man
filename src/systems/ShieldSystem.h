// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"
#include <vector>

struct Transform;

class ShieldSystem: public ecs::System {
public:

	ShieldSystem();
	virtual ~ShieldSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message&) override;

	void summonShields();
private:
	int _X; int _N; int _T; int _count;
	std::vector<int> _fruits;
	bool _inmunity, _active;
};

