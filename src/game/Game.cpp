// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/PacManSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

//GAMESTATES
#include "GameStates/NewGameState.h"
#include "GameStates/NewRoundState.h"
#include "GameStates/RunningState.h"
#include "GameStates/PausedState.h"
#include "GameStates/GameOverState.h"

using ecs::EntityManager;

Game::Game() :
		_mngr(), //
		_pacmanSys(), //
		_renderSys(), //
		_collisionSys(), //
		_ghostSys(), //
		_foodSys(), //
		_immSys(){
}

Game::~Game() {
	delete _mngr;

	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
		"resources/config/resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
			<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
			<< std::endl;
		return false;

	}

	// Create the manager
	_mngr = new EntityManager();

	// Create the states
	_newgame_state = new NewGameState();
	_newround_state = new NewRoundState();
	_runing_state = new RunningState();
	_paused_state = new PausedState();
	_gameover_state = new GameOverState();
	_state = _newgame_state;

	// add the systems
	_pacmanSys = _mngr->addSystem<PacManSystem>();
	_renderSys = _mngr->addSystem<RenderSystem>();
	_collisionSys = _mngr->addSystem<CollisionsSystem>();
	_ghostSys = _mngr->addSystem<GhostSystem>();
	_foodSys = _mngr->addSystem<FoodSystem>();
	_immSys = _mngr->addSystem<ImmunitySystem>();

	return true;
}

bool Game::initSglSdl() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("PacMan, Stars, ...", 800, 600,
		"resources/config/resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
			<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
			<< std::endl;
		return false;

	}

	return true;
}

void Game::start() {
	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}
		sdlutils().clearRenderer();
		_state->update();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

ecs::EntityManager* 
Game::getManager() {
	return _mngr;
}


void
Game::setState(State s)
{
	_state->leave();
	switch (s)
	{
	case RUNNING:
		_state = _runing_state;
		break;
	case PAUSED:
		_state = _paused_state;
		break;
	case NEWGAME:
		_state = _newgame_state;
		break;
	case NEWROUND:
		_state = _newround_state;
		break;
	case GAMEOVER:
		_state = _gameover_state;
		break;
	default:
		break;
	}
	_state->enter();
}