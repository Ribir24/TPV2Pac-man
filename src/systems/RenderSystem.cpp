// This file is part of the course TPV2@UCM - Samir Genaim

#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/FramedImage.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {
}

void RenderSystem::initSystem() {
}

void RenderSystem::update() {
	drawFood();
	drawGhosts();
	drawPacMan();
	drawHearts();
}

void RenderSystem::drawGhosts() {
	for (auto e : _mngr->getEntities(ecs::grp::GHOSTS)) {

		auto tr = _mngr->getComponent<Transform>(e);
		auto tex = _mngr->getComponent<FramedImage>(e);
		drawFrame(tr, tex);
	}
}

void RenderSystem::drawPacMan() {
	auto e = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto tr = _mngr->getComponent<Transform>(e);
	auto tex = _mngr->getComponent<FramedImage>(e);
	drawFrame(tr, tex);
}

void RenderSystem::drawHearts() {
	auto pc = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pcHealth = _mngr->getComponent<Health>(pc);
	int health = pcHealth->_lives;

	auto& heart = sdlutils().images().at("heart");

	for (int i = 0; i < health; i++) {
		SDL_FRect dest;
		dest.x = 10 + i * (heart.width() / 3 + 5);
		dest.y = 10;
		dest.w = heart.width() / 3;
		dest.h = heart.height() / 3;

		heart.render(dest, 0.0f);
	}
}

void
RenderSystem::drawFood() {
	for (auto e : _mngr->getEntities(ecs::grp::FOOD)) {
		auto tr = _mngr->getComponent<Transform>(e);
		auto tex = _mngr->getComponent<FramedImage>(e);
		drawFrame(tr, tex);
	}
}

void 
RenderSystem::draw(Transform *tr, const Texture *tex) {
	SDL_FRect dest = build_sdlfrect(tr->_pos, tr->_width, tr->_height);

	assert(tex != nullptr);
	tex->render(dest, tr->_rot);
}

void 
RenderSystem::drawFrame(Transform* tr, FramedImage* tex) {
	int currentFrame = tex->_animationFrames[tex->_iCurrentFrame];

	SDL_FRect src = {
		(currentFrame % tex->_iCols) * tex->_fFrameWidth, 
		(currentFrame / tex->_iCols) * tex->_fFrameHeight,
		tex->_fFrameWidth,
		tex->_fFrameHeight
	};
	SDL_FRect dest = build_sdlfrect(tr->_pos, tr->_width, tr->_height);

	assert(tex->_tex != nullptr);
	tex->_tex->render(src, dest, tr->_rot);

	auto& vt = sdlutils().virtualTimer();
	vt.regCurrTime();
	Uint32 currentTime = static_cast<Uint32>(vt.currTime());

	if (currentTime - tex->_fLastFrameUpdate > tex->_iAnimSpeed) {
		tex->_fLastFrameUpdate = currentTime;
		tex->_iCurrentFrame = (tex->_iCurrentFrame + 1) % (tex->_animationFrames.size());
	}
}