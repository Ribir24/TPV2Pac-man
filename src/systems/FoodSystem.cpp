#include "FoodSystem.h"

#include "../game/Game.h"

#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/Forbiden.h"
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
            //if (rand() % 10 == 0) {
            //    auto m = _mngr->addComponent<Miracle>(e);
            //    // datos del componente
            //    m->_lastTime = sdlutils().virtualTimer().currTime();
            //    m->_N = 10000 + rand() % 10000; // de 10 a 20 segundos
            //}

            //FRUTA PROHIBIDA
            if (rand() % 5 == 0) {
                auto m = _mngr->addComponent<Forbiden>(e);
                // datos del componente
                m->_lastTime = sdlutils().virtualTimer().currTime();
                m->_N = 10000 + rand() % 10000; // de 10 a 20 segundos
                std::cout << "Spawn prohibida" << std::endl;
            }
        }
    }
}

void 
FoodSystem::update() {
    auto& food = _mngr->getEntities(ecs::grp::FOOD);
    Uint32 now = sdlutils().virtualTimer().currTime();

    for (auto e : food) {
        if (_mngr->hasComponent<Forbiden>(e)) {
            auto forb = _mngr->getComponent<Forbiden>(e);
            auto img = _mngr->getComponent<FramedImage>(e);
            
            assert(forb && img);

            Uint32 elapsed = now - forb->_lastTime; // tiempo desde que empezó el estado actual

            if (!forb->_active && elapsed >= forb->_N) {
                auto pmTR = _mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::PACMAN));
                auto fTR = _mngr->getComponent<Transform>(e);
                if ((pmTR->_pos - fTR->_pos).magnitude() > 100.0f) {
                    // PASAR A PROHIBIDO
                    forb->_active = true;
                    forb->_lastTime = now;           // reinicia el contador para el estado milagroso
                    forb->_M = 1000 + rand() % 4000; // 1–5 s
                    img->_animationFrames = { 15 };
                    std::cout << "SE VOLVIO PROHIBIDA" << std::endl;
                }
                else {
                    // QUEDARSE NORMAL
                    std::cout << "Me quedo normal" << std::endl;
                    forb->_lastTime = now;  // reinicia el contador para el estado normal
                }
            }
            else if (forb->_active && elapsed >= forb->_M) {
                // VOLVER A NORMAL
                std::cout << "De vuelta a la normalidad" << std::endl;
                forb->_active = false;
                forb->_lastTime = now;           // reinicia el contador para el estado normal
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