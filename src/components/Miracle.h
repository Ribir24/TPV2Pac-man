// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 

class Texture;

struct Miracle : public ecs::Component {

	Miracle() :
		_active(false),
		_lastTime(0),
		_N(0),
		_M(0) {
	}

	virtual ~Miracle() {
	}

	bool _active;

	Uint32 _lastTime;
	Uint32 _N; // tiempo normal
	Uint32 _M; //tiempo en milagroso
};

