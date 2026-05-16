// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

struct Clonable : public ecs::Component {

	Clonable() :
		_N(), _M() {
	}

	Clonable(int N, float M) :
		_N(N), _M(M) {
	}

	virtual ~Clonable() {
	}

	int _N;
	float _M;;
};