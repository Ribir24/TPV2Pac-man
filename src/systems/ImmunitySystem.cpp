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
        Uint32 now = SDL_GetTicks();
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
    if (msg.id == _m_IMMUNITY_START) {
        _active = true;
        _startTime = SDL_GetTicks();
        auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
        _mngr->getComponent<Immunity>(pc)->_active = true;
    }
}