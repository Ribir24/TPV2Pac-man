// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include <vector>
#include <SDL.h> 

class Texture;

struct FramedImage : public ecs::Component {

	FramedImage() :
		_tex() {
	}

	FramedImage(const Texture* tex) :
		_tex(tex) {
	}

	virtual ~FramedImage() {
	}

	const Texture* _tex;
	float _fFrameWidth, _fFrameHeight;
	int _iCols, iRows;
	Uint32 _iAnimSpeed;
	Uint32 _fLastFrameUpdate;
	int _iCurrentFrame;

	std::vector<int> _animationFrames;
};

#pragma once
