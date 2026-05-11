#pragma once

#include "GameState.h"
#include "../../game/Game.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../../components/Transform.h"

class PausedState : public GameState {
public:
    PausedState();
    ~PausedState() {}

    void enter() override;
    void leave() override;
    void update() override;

private:

};