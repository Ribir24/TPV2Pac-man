#include "NewGameState.h"

NewGameState::
NewGameState(){}

NewGameState::
~NewGameState()
{
}

void 
NewGameState::update()
{
    auto& text = sdlutils().msgs().at("start");
    text.render(sdlutils().width() / 3, sdlutils().height() / 2);

    if (ih().keyDownEvent()) {
        Message m;
        m.id = _m_NEW_GAME;
        Game::Instance()->getManager()->send(m);
        sdlutils().soundEffects().at("pacman_intro").play();
        Game::Instance()->setState(Game::State::NEWROUND);
    }
}