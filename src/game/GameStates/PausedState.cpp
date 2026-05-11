#include "PausedState.h"
#include "../../game/Game.h"
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"

PausedState::PausedState(){
}

void
PausedState::enter() {
    sdlutils().virtualTimer().pause();
}

void
PausedState::leave() {
    sdlutils().virtualTimer().resume();
}

void
PausedState::update() {
    auto& text = sdlutils().msgs().at("paused");
    text.render(sdlutils().width() / 3.5, sdlutils().height() / 2);

    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::State::RUNNING);
    }
}