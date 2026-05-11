#pragma once

#include "GameState.h"
#include "../../game/Game.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"

class GameOverState : public GameState {
public:
    GameOverState() {};
    ~GameOverState() {};

    void enter() {} ;
    void leave() {};
    void update() override;
};