#include "BreakableBrick.h"


BreakableBrick::BreakableBrick(float posX, float posY, int type)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BREAKABLEBRICK));
	tag = EntityType::BREAKABLEBRICK;

	this->posX = posX;
	this->posY = posY;
	health = 1;
	isDead = false;
	brickType = type - 1;
}

BreakableBrick::~BreakableBrick() {}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		isDead = true;
		return;
	}
}

void BreakableBrick::Render()
{
	if (isDead)
		return;

	animationSet->at(brickType)->Render(-direction, posX, posY);

	RenderBoundingBox();
}

void BreakableBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + BBRICK_BBOX_WIDTH;
		b = posY + BBRICK_BBOX_HEIGHT;
	}
}
