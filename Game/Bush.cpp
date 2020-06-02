#include "Bush.h"

Bush::Bush(float posX, float posY, LPGAMEENTITY player)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BUSH));
	tag = EntityType::BUSH;

	this->posX = posX;
	this->posY = posY;
	health = 1;
	isDead = false;
	this->player = player;
	isPlayerInside = false;
}

Bush::~Bush() {}

void Bush::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (IsCollidingObject(player))
		isPlayerInside = true;
	else
		isPlayerInside = false;
}

void Bush::Render()
{
	int alpha = ENTITY_ALPHA_RENDER;
	if (isPlayerInside)
		alpha = BUSH_FADED;

	animationSet->at(0)->Render(-direction, posX, posY, alpha);

	RenderBoundingBox();
}

void Bush::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + BUSH_BBOX_WIDTH;
		b = posY + BUSH_BBOX_HEIGHT;
	}
}