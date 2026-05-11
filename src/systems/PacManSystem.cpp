// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../game/Game.h"

#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/Immunity.h"
#include "../components/Health.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

PacManSystem::PacManSystem() :
		_pmTR(nullptr),
		_speed(2.5f) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	auto pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	_pmTR = _mngr->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	//SPRITESHEET
	auto fi = _mngr->addComponent<FramedImage>(pacman, &sdlutils().images().at("sprites"));

	fi->_iCols = 8;
	fi->iRows = 8;
	fi->_fFrameWidth = sdlutils().images().at("sprites").width() / 8;
	fi->_fFrameHeight = sdlutils().images().at("sprites").height() / 8;

	//ANIMACION
	fi->_animationFrames = { 0, 1 };
	fi->_iCurrentFrame = 0;
	fi->_iAnimSpeed = 100;
	fi->_fLastFrameUpdate = 0;

	_mngr->addComponent<Immunity>(pacman);
	_mngr->addComponent<Health>(pacman);
}

void PacManSystem::update() {
	auto &ihldr = ih();
	_pmTR->_vel = Vector2D(0, 0);
	if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // go right
		_pmTR->_rot = 90.0f;
		_pmTR->_vel = Vector2D(_speed, 0);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // go left
		_pmTR->_rot = 270.0f;
		_pmTR->_vel = Vector2D(-_speed, 0);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // go up
		_pmTR->_rot = 0.0f;
		_pmTR->_vel = Vector2D(0, -_speed);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // go down
		_pmTR->_rot = 180.0f;
		_pmTR->_vel = Vector2D(0, _speed);
	}
	// move the pacman
	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}
}

void PacManSystem::recieve(const Message& msg) {
	if (msg.id == _m_PACMAN_GHOST_COLLISION) {
		_mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::PACMAN))->_lives--;
		auto pcHealth = _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::PACMAN));
		int health = pcHealth->_lives;

		if (health <= 0) Game::Instance()->setState(Game::State::GAMEOVER);
		else Game::Instance()->setState(Game::State::NEWROUND);
	}
	else if (msg.id == _m_NEW_GAME) {
		_pmTR->_pos.setX((sdlutils().width() - _pmTR->_width) / 2.0f);
		_pmTR->_pos.setY((sdlutils().height() - _pmTR->_height) / 2.0f);

		auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
		_mngr->getComponent<Immunity>(pacman)->_active = false;
		_mngr->getComponent<Health>(pacman)->_lives = 3;
	}
	else if (msg.id == _m_ROUND_START) {
		_pmTR->_pos.setX((sdlutils().width() - _pmTR->_width) / 2.0f);
		_pmTR->_pos.setY((sdlutils().height() - _pmTR->_height) / 2.0f);

		auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
		_mngr->getComponent<Immunity>(pacman)->_active = false;
	}
}