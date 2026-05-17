#include "FullSystem.h"

#include "../components/Immunity.h"

FullSystem::FullSystem() :
    _active(false),
    _timer(0),
    _amountToFull(5),
    _fullDuration(5000),
    _interval(2000),
    _foodEaten(0),
    _lastTick(sdlutils().virtualTimer().currTime())
{
}

FullSystem::~FullSystem() {
}

void
FullSystem::initSystem() {
} 

void 
FullSystem::update() {
    Uint32 now = sdlutils().virtualTimer().currTime();
    float dt = now - _lastTick;
    _lastTick = now;

    while (!_foodEaten.empty() && now - _foodEaten[0] > _interval) {
        _foodEaten.erase(_foodEaten.begin());
    }

    if (_foodEaten.size() >= _amountToFull) {
        _foodEaten.clear();
        _active = true;
        _timer = 0;
        Message msg;
        msg.id = _m_FULL_START;
        _mngr->send(msg);
    }

    if (_active) {
        _timer += dt; 
        if (_timer >= _fullDuration) {
            _timer = 0;
            _active = false;
            Message msg;
            msg.id = _m_FULL_END;
            _mngr->send(msg);
        }
    }
}

void 
FullSystem::recieve(const Message& msg) {
    if (msg.id == _m_PACMAN_FOOD_COLLISION && !_active) {
        _foodEaten.push_back(sdlutils().virtualTimer().currTime());
    }
    else if (msg.id == _m_ROUND_OVER || msg.id == _m_ROUND_START) {
        Message msg;
        msg.id = _m_FULL_END;
        _mngr->send(msg);
        _active = false;
        _timer = 0;
    }
}