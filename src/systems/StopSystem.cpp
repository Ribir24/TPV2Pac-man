#include "StopSystem.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Immunity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/GhostSystem.h"

StopSystem::StopSystem() :
    _stopTimer(10000.0f),
    _stopInterval(10000.0f),
    _stopDuration(5000.0f),
    _active(false),
    _lastTick(sdlutils().virtualTimer().currTime()) {
}

StopSystem::~StopSystem() {
}

void 
StopSystem::initSystem() {
}

void 
StopSystem::update() {
    auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);

    Uint32 now = sdlutils().virtualTimer().currTime();
    float dt = now - _lastTick;
    _lastTick = now;
    _stopTimer += dt;

    if (!_active && _stopTimer >= _stopInterval && ih().isKeyDown(SDL_SCANCODE_B)) {
        _stopTimer = 0.0f;
        _active = true;
        _mngr->getSystem<GhostSystem>()->spawnGhost();
        Message msg;
        msg.id = _m_STOP_START;
        _mngr->send(msg);
    }
    else if (_active && _stopTimer >= _stopDuration) {
        _active = false;
        _stopTimer = 0.0f;
        Message msg;
        msg.id = _m_STOP_END;
        _mngr->send(msg);
    }
}
