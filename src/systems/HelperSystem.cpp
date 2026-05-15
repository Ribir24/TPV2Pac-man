#include "HelperSystem.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Immunity.h"
#include "../components/Health.h"
#include "../components/Mortal.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/InputHandler.h"

HelperSystem::HelperSystem() :
    _spawnTimer(0.0f),
    _spawnInterval(5000.0f),
    _N(2),
    _lastTick(sdlutils().virtualTimer().currTime()),
    MinT(10000),
    MaxT(20000),
    mortProb(80),
    _V(90)
{
}

HelperSystem::~HelperSystem() {
}

void 
HelperSystem::initSystem() {
}

void 
HelperSystem::update() {
    auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
    auto health = _mngr->getComponent<Health>(pc);

    auto& ihldr = ih();
    if (ihldr.isKeyDown(SDL_SCANCODE_A) && health->_lives > 1) { // SPAWN HELPER
        for (int i = 0; i < _N; i++) {
            spawnHelper();
        }

        health->_lives--;
    }

    auto& helpers = _mngr->getEntities(ecs::grp::HELPERS);
    auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);

    Uint32 now = sdlutils().virtualTimer().currTime();
    float dt = now - _lastTick;
    _lastTick = now;

    // so its position can be tracked
    auto posPM = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::PACMAN))->_pos;
    float V = 2.0f;

    for (auto e : helpers) {
        if (_mngr->isAlive(e)) {
            
            Transform* nearestGhost = nullptr;
            auto helperTR = _mngr->getComponent<Transform>(e);
            float minDist = FLT_MAX;

            for (auto g : ghosts) {
                auto ghostTR = _mngr->getComponent<Transform>(g);

                float dist = (ghostTR->_pos - helperTR->_pos).magnitude();
                if (dist < minDist) {
                    minDist = dist;
                    nearestGhost = ghostTR;
                }
            }
          
            if (nearestGhost != nullptr) {
                Vector2D dir =(nearestGhost->_pos - helperTR->_pos).normalize();

                helperTR->_vel = dir * V;
            }
            else {
                helperTR->_vel = Vector2D(0.0f, 0.0f);
            }

            helperTR->_pos = helperTR->_pos + helperTR->_vel;

            //QUE VAYAN MURIENDO
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
HelperSystem::spawnHelper() {
    auto e = _mngr->addEntity(ecs::grp::HELPERS);
    auto ghostTr = _mngr->addComponent<Transform>(e);
    float size = 40.0f;


    Vector2D pos = Vector2D(0 + rand() % (int)(sdlutils().width() - size), 0 + rand() % (int)(sdlutils().height() - size));

    ghostTr->init(pos, Vector2D(1.0f, 1.0f), size, size, 0.0f);

    //SPRITESHEET
    auto fi = _mngr->addComponent<FramedImage>(e, &sdlutils().images().at("sprites"));

    fi->_iCols = 8;
    fi->iRows = 8;
    fi->_fFrameWidth = sdlutils().images().at("sprites").width() / 8;
    fi->_fFrameHeight = sdlutils().images().at("sprites").height() / 8;

    //ANIMACION
    fi->_animationFrames = { 7 };
    fi->_iCurrentFrame = 0;
    fi->_iAnimSpeed = 100;
    fi->_fLastFrameUpdate = 0;

    //MORTAL
    auto mort = _mngr->addComponent<Mortal>(e);
    mort->_T = 5000;
}

void HelperSystem::recieve(const Message& msg) {
    auto& helpers = _mngr->getEntities(ecs::grp::HELPERS);

    if (msg.id == _m_ROUND_OVER || msg.id == _m_PACMAN_GHOST_COLLISION) {
        for (auto e : helpers) {
            _mngr->setAlive(e, false);
        }
    }
}