#pragma once

#include "GameState.h"
#include "../../game/Game.h"
#include "../../sdlutils/InputHandler.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/Font.h"

class NewGameState : public GameState {
public:
	NewGameState();
	~NewGameState();
    void enter() override {}
    void leave() override {}
    void update() override;
private:
};