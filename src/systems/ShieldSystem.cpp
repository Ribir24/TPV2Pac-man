// This file is part of the course TPV2@UCM - Samir Genaim

#include "ShieldSystem.h"

#include "../game/Game.h"

#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/Immunity.h"
#include "../components/Health.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

ShieldSystem::ShieldSystem() :
		_X(40),
		_fruits(0),
		_inmunity(false),
		_active(false),
		_N(0),
		_T(15000),
		_count(0){
}

ShieldSystem::~ShieldSystem() {
}

void ShieldSystem::initSystem() {
}

void ShieldSystem::update() {
	Uint32 now = sdlutils().virtualTimer().currTime();
	if (_fruits[0] > now + 15000 && !_active) {
		_fruits.erase(_fruits.begin());
	}
	else if (_fruits.size() >= 15 && !_active){  
		_fruits.clear();
		_active = true;
		summonShields();
		_count = sdlutils().virtualTimer().currTime();
	}

	if (_active) {
		auto& stars = _mngr->getEntities(ecs::grp::STARS);
		auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
		auto pcTr = _mngr->getComponent<Transform>(pc);
		int i = 0;
		for (auto e : stars) {
			if (_mngr->isAlive(e)) {
				auto posSt = _mngr->getComponent<Transform>(e);
				if (i == 0) {
					posSt->_pos.setX(pcTr->_pos.getX() + _X);
					posSt->_pos.setX(pcTr->_pos.getY());
				}
				else if (i == 1) {
					posSt->_pos.setX(pcTr->_pos.getX() - _X);
					posSt->_pos.setX(pcTr->_pos.getY());
				}
				else if (i == 2) {
					posSt->_pos.setX(pcTr->_pos.getX());
					posSt->_pos.setX(pcTr->_pos.getY() + _X);
				}
				else if (i == 3) {
					posSt->_pos.setX(pcTr->_pos.getX());
					posSt->_pos.setX(pcTr->_pos.getY() - _X);
				}
				
				i++;
			}
		}

		if (sdlutils().virtualTimer().currTime() > _count + _T) {
			for (auto e : stars) {
				_mngr->setAlive(e, false);
			}
		}
	}
}

void ShieldSystem::recieve(const Message& msg) {
	if (msg.id == _m_PACMAN_FOOD_COLLISION && !_inmunity && _active) {
		_fruits.push_back(sdlutils().virtualTimer().currTime());
	}
	else if (msg.id == _m_IMMUNITY_START) {
		_inmunity = true;
	}
	else if (msg.id == _m_IMMUNITY_END) {
		_inmunity = false;
	}
}

void ShieldSystem::summonShields() {
	for (int i = 0; i < 4; i++) {
		auto e = _mngr->addEntity(ecs::grp::STARS);
		auto starTr = _mngr->addComponent<Transform>(e);

		Vector2D pos = Vector2D(0, 0);
		float size = 40.0;

		//SPRITESHEET
		auto fi = _mngr->addComponent<FramedImage>(e, &sdlutils().images().at("sprites"));

		fi->_iCols = 8;
		fi->iRows = 8;
		fi->_fFrameWidth = sdlutils().images().at("sprites").width() / 8;
		fi->_fFrameHeight = sdlutils().images().at("sprites").height() / 8;

		//ANIMACION
		fi->_animationFrames = { 7 };
		fi->_iCurrentFrame = 0;
		fi->_iAnimSpeed = 100;
		fi->_fLastFrameUpdate = 0;
	}
}
