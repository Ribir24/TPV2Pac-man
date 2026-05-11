#include "ImmunitySystem.h"

#include "../components/Immunity.h"

ImmunitySystem::ImmunitySystem() :
    _active(false),
    _startTime(0) {
}

ImmunitySystem::~ImmunitySystem() {
}

void
ImmunitySystem::initSystem() {
}

void 
ImmunitySystem::update() {
    if (_active) {
        Uint32 now = sdlutils().virtualTimer().currTime();
        if (now - _startTime >= 10000) {
            _active = false;
            Message msg;
            msg.id = _m_IMMUNITY_END;
            _mngr->send(msg);
            auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
            _mngr->getComponent<Immunity>(pc)->_active = false;
        }
    }
}

void 
ImmunitySystem::recieve(const Message& msg) {
    if (msg.id == _m_PACMAN_MIRACLE_FOOD_COLLISION && !_mngr->getComponent<Immunity>(_mngr->getHandler(ecs::hdlr::PACMAN))->_active) {
        _active = true;
        _startTime = sdlutils().virtualTimer().currTime();
        auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
        _mngr->getComponent<Immunity>(pc)->_active = true;
        Message mIm;
        mIm.id = _m_IMMUNITY_START;
        _mngr->send(mIm);
    }
}