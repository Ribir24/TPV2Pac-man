#include "FullSystem.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Immunity.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"


FullSystem::FullSystem() :
    _timer(0.0f),
    _interval(5000.0f),
    _maxFruit(2),
    _active(false),
    _lastTick(sdlutils().virtualTimer().currTime()) {
}

FullSystem::~FullSystem() {
}

void 
FullSystem::initSystem() {
}

void 
FullSystem::update() {
    if (_active) {
        Uint32 now = sdlutils().virtualTimer().currTime();
        float dt = now - _lastTick;
        _lastTick = now;
        _timer += dt;
        if (_timer >= _interval) {
            _active = false;
            _timer = 0.0f;
            Message m;
            m.id = _m_FULL_END;
            _mngr->send(m);
        }
    }
}

void FullSystem::recieve(const Message& msg) {
    if (msg.id == _m_FULL_START) {
        _timer = 0.0f;
        _active = true;
        _lastTick = sdlutils().virtualTimer().currTime();
    }
    else if (msg.id == _m_ROUND_OVER) {
        if (_active) {
            Message m;
            m.id = _m_FULL_END;
            _mngr->send(m);
        }
        _active = false;
        _timer = 0.0f;
    }
}