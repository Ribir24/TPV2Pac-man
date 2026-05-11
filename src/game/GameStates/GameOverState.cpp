#include "GameOverState.h"

void GameOverState::enter()
{
    auto& food = Game::Instance()->getManager()->getEntities(ecs::grp::FOOD);

    won = true;
    int i = 0;
    while (won && i < food.size()){
        if (Game::Instance()->getManager()->isAlive(food[i])) won = false;
        i++;
    }
}
void
GameOverState::update()
{
    if (won) {
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