#include "GameOverState.h"

void
GameOverState::update()
{
    auto& food = Game::Instance()->getManager()->getEntities(ecs::grp::FOOD);
    if (food.size() == 0) {
        auto& winText = sdlutils().msgs().at("win");
        winText.render(sdlutils().width() / 3.5, sdlutils().height() / 2);
    }
    else {
        auto& looseText = sdlutils().msgs().at("loose");
        looseText.render(sdlutils().width() / 3.5, sdlutils().height() / 2);
    }

    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::State::NEWGAME);
    }
}