#pragma once

#include "GameState.h"
#include "../../game/Game.h"


class RunningState : public GameState {
public:
    RunningState();
    ~RunningState();

    void enter() override {}
    void leave() override {}
    void update() override;

private:


    int _lastAst = 0;
    int _astSpawnInterval = 5000;
};