#include "Brick.h"

Brick::Brick(float posX, float posY, int brickType)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BRICK));
	tag = EntityType::BRICK;

	this->posX = posX;
	this->posY = posY;
	this->brickType = brickType - 1;	//type = 1 su dung vi tri 0
	isStaticObj = true;
}

Brick::~Brick() {}

void Brick::Render()
{
	animationSet->at(brickType)->Render(-direction, posX, posY);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX;
	t = posY;
	r = posX + BRICK_BBOX_WIDTH;
	b = posY + BRICK_BBOX_HEIGHT;
}
