// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/EntityManager.h"
#include "GameStates/GameState.h"
#include <vector>

#include "../utils/Singleton.h"

#include "../ecs/ecs.h"

class GameState;

class Game : public Singleton<Game> {
	friend Singleton<Game>;
public:
	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};
	void setState(State s);

	bool init();
	void start();

	ecs::EntityManager* getManager();
private:
	Game();
	virtual ~Game();

	bool initSglSdl();

	ecs::EntityManager *_mngr;
	ecs::System *_pacmanSys;
	ecs::System *_renderSys;
	ecs::System *_collisionSys;
	ecs::System* _ghostSys;
	ecs::System* _foodSys;
	ecs::System* _immSys;
	ecs::System* _fullSys;

	GameState* _state;
	GameState* _paused_state;
	GameState* _runing_state;
	GameState* _newgame_state;
	GameState* _newround_state;
	GameState* _gameover_state;
};

