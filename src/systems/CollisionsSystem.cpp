// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../components/Miracle.h"
#include "../components/Immunity.h"
#include "../components/Health.h"
#include "../components/Resistant.h"
#include "../ecs/EntityManager.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"

CollisionsSystem::CollisionsSystem(): _full(false) {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	
	auto &food = _mngr->getEntities(ecs::grp::FOOD);
	auto n = food.size();
	if (!_full) {
		for (auto i = 0u; i < n; i++) {
			auto e = food[i];
			if (_mngr->isAlive(e)) { // if the food is active (it might have died in this frame) 
				// the Food's Transform
				//
				auto eTR = _mngr->getComponent<Transform>(e);

				// check if PacMan collides with the food (i.e., eat it)
				if (Collisions::collides(
					pTR->_pos, pTR->_width, pTR->_height,
					eTR->_pos, eTR->_width, eTR->_height)) {
					auto immu = _mngr->getComponent<Miracle>(e);
					if (immu != nullptr && immu->_active) {
						Message m;
						m.id = _m_PACMAN_MIRACLE_FOOD_COLLISION;
						_mngr->send(m);
					}
					_mngr->setAlive(e, false);
					sdlutils().soundEffects().at("pacman_eat").play();
					Message m;
					m.id = _m_PACMAN_FOOD_COLLISION;
					_mngr->send(m);
				}
			}
		}
	}

	auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto nG = ghosts.size();
	for (auto i = 0u; i < nG; i++) {
		auto e = ghosts[i];
		if (_mngr->isAlive(e)) { // if the ghost is active (it might have died in this frame) 
			// the ghost's Transform
			//
			auto eTR = _mngr->getComponent<Transform>(e);

			// check if PacMan collides with the ghost
			if (Collisions::collides(
				pTR->_pos, pTR->_width, pTR->_height,
				eTR->_pos, eTR->_width, eTR->_height)) {

				auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
				auto immComp = _mngr->getComponent<Immunity>(pc);
				assert(immComp != nullptr);

				bool imm = immComp->_active;
				if (imm) {
					if (!_full) {
						if (_mngr->hasComponent<Resistant>(e) && _mngr->getComponent<Resistant>(e)->_T > 0) {
							Vector2D newPos;
							bool valid = false;

							while (!valid) {
								float x = rand() % sdlutils().width();
								float y = rand() % sdlutils().height();

								newPos = Vector2D(x, y);

								float dist = (pTR->_pos - newPos).magnitude();

								if (dist <= 100.0) valid = true;
							}
							eTR->_pos = newPos;
						}
						else {
							_mngr->setAlive(e, false);
							sdlutils().soundEffects().at("pacman_chomp").play();
						}
					}
				}
				else {
					Message m;
					m.id = _m_PACMAN_GHOST_COLLISION;
					_mngr->send(m);
					sdlutils().soundEffects().at("pacman_death").play();
				}
			}
		}
	}
}

void CollisionsSystem::recieve(const Message& msg) {
	if (msg.id == _m_FULL_START) {
		_full = true;
	}
	else if (msg.id == _m_FULL_END) {
		_full = false;
	}
}