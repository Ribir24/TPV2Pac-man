#include "GhostSystem.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Immunity.h"
#include "../components/Mortal.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"


GhostSystem::GhostSystem() :
    _spawnTimer(0.0f),
    _spawnInterval(5000.0f),
    _maxGhost(10),
    _lastTick(sdlutils().virtualTimer().currTime()),
    MinT(10000),
    MaxT(20000),
    mortProb(80),
    _V(90)
{
}

GhostSystem::~GhostSystem() {
}

void 
GhostSystem::initSystem() {
}

void 
GhostSystem::update() {
    auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);

    Uint32 now = sdlutils().virtualTimer().currTime();
    float dt = now - _lastTick;
    _lastTick = now;
    _spawnTimer += dt;

    auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
    bool imm = _mngr->getComponent<Immunity>(pc)->_active;

    if (_spawnTimer >= _spawnInterval && ghosts.size() < _maxGhost && !imm) {
        spawnGhost();
        _spawnTimer = 0.0f;
    }

    // so its position can be tracked
    auto posPM = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::PACMAN))->_pos;

    for (auto e : ghosts) {
        if (_mngr->isAlive(e)) {
            auto posF = _mngr->getComponent<Transform>(e);

            if ((rand() % 200) == 0) { // 0.005 probabilidad
                Vector2D dir = (posPM - posF->_pos).normalize();
                posF->_vel = dir * 1.1f;
            }
            posF->_pos = posF->_pos + posF->_vel;

            if (posF->_pos.getX() < 0 || posF->_pos.getX() + posF->_width > sdlutils().width())   posF->_vel.setX(-posF->_vel.getX());
            if (posF->_pos.getY() < 0 || posF->_pos.getY() + posF->_height > sdlutils().height()) posF->_vel.setY(-posF->_vel.getY());

            auto mort = _mngr->getComponent<Mortal>(e);
            if (mort != nullptr) {
                mort->_T -= dt;
                if (mort->_T <= 0) {
                    _mngr->setAlive(e, false);
                }
            }
        }
    }
}


void 
GhostSystem::spawnGhost() {
    auto e = _mngr->addEntity(ecs::grp::GHOSTS);
    auto ghostTr = _mngr->addComponent<Transform>(e);
    float size = 40.0f;

    int corner = rand() % 4;
    Vector2D pos;

    if (corner == 0)      pos = Vector2D(0, 0); // top izq
    else if (corner == 1) pos = Vector2D(sdlutils().width() - size, 0); // top der
    else if (corner == 2) pos = Vector2D(0, sdlutils().height() - size); // bottom izq
    else                  pos = Vector2D(sdlutils().width() - size, sdlutils().height() - size); //bottom der

    ghostTr->init(pos, Vector2D(1.0f, 1.0f), size, size, 0.0f);

    //SPRITESHEET
    auto fi = _mngr->addComponent<FramedImage>(e, &sdlutils().images().at("sprites"));

    fi->_iCols = 8;
    fi->iRows = 8;
    fi->_fFrameWidth = sdlutils().images().at("sprites").width() / 8;
    fi->_fFrameHeight = sdlutils().images().at("sprites").height() / 8;

    //ANIMACION
    fi->_animationFrames = { 32, 33, 34, 35, 36, 37, 38, 39 };
    fi->_iCurrentFrame = 0;
    fi->_iAnimSpeed = 100;
    fi->_fLastFrameUpdate = 0;

    if (rand() % 100 < mortProb) {
        auto mort = _mngr->addComponent<Mortal>(e);
        mort->_T = MinT + rand() % (MaxT - MinT + 1);
        mort->_V = _V;
        if      (corner == 0) mort->_pos = Vector2D(0, 0); // top izq
        else if (corner == 1) mort->_pos = Vector2D(sdlutils().width() - size, 0); // top der
        else if (corner == 2) mort->_pos = Vector2D(0, sdlutils().height() - size); // bottom izq
        else                  mort->_pos = Vector2D(sdlutils().width() - size, sdlutils().height() - size); //bottom der
    }
}

void GhostSystem::recieve(const Message& msg) {
    auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);

    if (msg.id == _m_IMMUNITY_START) {
        for (auto e : ghosts) {
            if (_mngr->isAlive(e) && _mngr->hasComponent<FramedImage>(e)) {
                auto img = _mngr->getComponent<FramedImage>(e);
                img->_animationFrames = { 30, 31 };
                img->_iCurrentFrame = 0;
            }
        }
    }
    else if (msg.id == _m_IMMUNITY_END) {
        for (auto e : ghosts) {
            if (_mngr->isAlive(e) && _mngr->hasComponent<FramedImage>(e)) {
                auto img = _mngr->getComponent<FramedImage>(e);
                img->_animationFrames = { 32, 33, 34, 35, 36, 37, 38, 39 };
                img->_iCurrentFrame = 0;
            }
        }
    }
    else if (msg.id == _m_PACMAN_GHOST_COLLISION || msg.id == _m_NEW_GAME) {
        for (auto e : ghosts) {
            _mngr->setAlive(e, false);
        }
    }
}