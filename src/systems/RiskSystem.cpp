// This file is part of the course TPV2@UCM - Samir Genaim

#include "RiskSystem.h"

#include "../components/Transform.h"
#include "../components/Miracle.h"
#include "../components/Immunity.h"
#include "../components/Health.h"
#include "../components/Weak.h"
#include "../components/FramedImage.h"
#include "../ecs/EntityManager.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"

RiskSystem::RiskSystem():
	_lastTick(sdlutils().virtualTimer().currTime()) 
{
	// TODO Auto-generated constructor stub
}

RiskSystem::~RiskSystem() {
	// TODO Auto-generated destructor stub
}

void RiskSystem::initSystem() {
}

void RiskSystem::update() {

	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	
	Uint32 now = sdlutils().virtualTimer().currTime();
	float dt = now - _lastTick;
	_lastTick = now;

	auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto nG = ghosts.size();
	bool summed = false;
	if (!_act && !_imm) {
		for (auto i = 0u; i < nG && !summed; i++) {
			auto e = ghosts[i];
			if (_mngr->isAlive(e)) { // if the ghost is active (it might have died in this frame) 
				// the ghost's Transform
				//
				auto eTR = _mngr->getComponent<Transform>(e);

				if ((pTR->_pos - eTR->_pos).magnitude() < 100.0f) {
					_count += dt;
					summed = true;
				}
			}
		}
		if (!summed) _count = 0;
	}
	if (!_act && _count >= _timeToAct) {
		_count = 0;
		_act = true;
		Message m;
		m.id = _m_SAFE_START;
		_mngr->send(m);
	}
	else if (_act) {
		_count += dt;
		if (_count >= _duration) {
			_count = 0;
			_act = false;
			Message m;
			m.id = _m_SAFE_END;
			_mngr->send(m);
		}
	}
}

void RiskSystem::recieve(const Message& msg) {

	if (msg.id == _m_IMMUNITY_START) {
		_imm = true;
	}
	else if (msg.id == _m_IMMUNITY_END) {
		_imm = false;
	}
}