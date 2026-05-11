#include "RunningState.h"
#include "../../game/Game.h"
#include "../../components/Health.h"
#include "../../sdlutils/InputHandler.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../utils/Collisions.h"

//SISTEMAS
#include "../../systems/PacManSystem.h"
#include "../../systems/CollisionsSystem.h"
#include "../../systems/GhostSystem.h"
#include "../../systems/FoodSystem.h"
#include "../../systems/ImmunitySystem.h"
#include "../../systems/RenderSystem.h"

RunningState::
RunningState() {}

RunningState::
~RunningState() {
}


void
RunningState::update() {
    if (ih().isKeyDown(SDL_SCANCODE_P) && ih().keyDownEvent()) {
        Game::Instance()->setState(Game::State::PAUSED);
    }
    else {
        auto mngr = Game::Instance()->getManager();

        mngr->getSystem<PacManSystem>()->update();
        mngr->getSystem<CollisionsSystem>()->update();
        mngr->getSystem<GhostSystem>()->update();
        mngr->getSystem<FoodSystem>()->update();
        mngr->getSystem<ImmunitySystem>()->update();

        mngr->getSystem<RenderSystem>()->update();

        mngr->refresh();
    }
}