#include "FoodSystem.h"

#include "../game/Game.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Miracle.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"


FoodSystem::FoodSystem() :
    _fils(6),
    _cols(8){
}

FoodSystem::~FoodSystem() {
}

void
FoodSystem::initSystem() {
    float windowWidth = sdlutils().width() / (float)_cols;
    float windowHeight = sdlutils().height() / (float)_fils;
    float size = 30.0f;

    for (int i = 0; i < _fils; i++) {
        for (int j = 0; j < _cols; j++) {
            auto e = _mngr->addEntity(ecs::grp::FOOD);
            auto foodTr = _mngr->addComponent<Transform>(e);

            Vector2D pos(j * windowWidth + (windowWidth - size) / 2.0f,
                         i * windowHeight + (windowHeight - size) / 2.0f);

            foodTr->init(pos, Vector2D(1.0f, 1.0f), size, size, 0.0f);

            //sprite
            auto fi = _mngr->addComponent<FramedImage>(e, &sdlutils().images().at("sprites"));

            fi->_iCols = 8;
            fi->iRows = 8;
            fi->_fFrameWidth = sdlutils().images().at("sprites").width() / 8;
            fi->_fFrameHeight = sdlutils().images().at("sprites").height() / 8;

            //ANIMACION
            fi->_animationFrames = { 12 };
            fi->_iCurrentFrame = 0;
            fi->_iAnimSpeed = 100;
            fi->_fLastFrameUpdate = 0;

            //FRUTA MILAGROSA
            if (rand() % 10 == 0) {
                auto m = _mngr->addComponent<Miracle>(e);
                // datos del componente
                m->_lastTime = SDL_GetTicks();
                m->_N = 10000 + rand() % 10000; // de 10 a 20 segundos
            }
        }
    }
}

void 
FoodSystem::update() {
    auto& food = _mngr->getEntities(ecs::grp::FOOD);
    Uint32 now = SDL_GetTicks();

    for (auto e : food) {
        if (_mngr->hasComponent<Miracle>(e)) {
            auto mir = _mngr->getComponent<Miracle>(e);
            auto img = _mngr->getComponent<FramedImage>(e);
            
            assert(mir && img);

            Uint32 elapsed = now - mir->_lastTime; // tiempo desde que empezó el estado actual

            if (!mir->_active && elapsed >= mir->_N) {
                // PASAR A MILAGROSO
                mir->_active = true;
                mir->_lastTime = now;           // reinicia el contador para el estado milagroso
                mir->_M = 1000 + rand() % 4000; // 1–5 s
                img->_animationFrames = { 15 };
            }
            else if (mir->_active && elapsed >= mir->_M) {
                // VOLVER A NORMAL
                mir->_active = false;
                mir->_lastTime = now;           // reinicia el contador para el estado normal
                img->_animationFrames = { 12 };
            }
        }
    }
}

void
FoodSystem::recieve(const Message& msg){
    if (msg.id == _m_PACMAN_FOOD_COLLISION) {
        auto& food = _mngr->getEntities(ecs::grp::FOOD);
        if (food.size() <= 1) {
            sdlutils().soundEffects().at("pacman_won").play();
            Game::Instance()->setState(Game::State::GAMEOVER);
        }
    }
    else if (msg.id == _m_NEW_GAME) {
        auto& food = _mngr->getEntities(ecs::grp::FOOD);
        for (auto e : food) _mngr->setAlive(e, false);
        initSystem();
    }
}