// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class Texture;
struct FramedImage;
struct Transform;

class RenderSystem: public ecs::System {
public:

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
private:
	void drawGhosts();
	void drawPacMan();
	void drawFood();
	void drawHearts();
	void draw(Transform *tr, const Texture *tex);
	void drawFrame(Transform* tr, FramedImage* tex);
};

