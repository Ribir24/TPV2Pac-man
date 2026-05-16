// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <SDL.h> 
#include "../utils/Vector2D.h"

class Texture;

struct Weak : public ecs::Component {

	Weak() :
		_N(0),
		_iniPos(0,0) {
	}

	virtual ~Weak() {
	}

	Vector2D _iniPos; //para regresar al chocarse
	Uint32 _N; // choques
};

