#include "NewRoundState.h"

class EntityManager;

NewRoundState::
NewRoundState(){}

NewRoundState::
~NewRoundState()
{}

void
NewRoundState::update()
{
    auto& text = sdlutils().msgs().at("newRound");
    text.render(sdlutils().width() / 3, sdlutils().height() / 2);
    if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Message m;
        m.id = _m_ROUND_START;
        Game::Instance()->getManager()->send(m);
        Game::Instance()->setState(Game::State::RUNNING);
    }
}