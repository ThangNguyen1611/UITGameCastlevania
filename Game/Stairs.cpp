#include "Stairs.h"

Stairs::Stairs(float posX, float posY, int stairDirection)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_STAIRS));
	tag = EntityType::STAIRS;

	this->posX = posX;
	this->posY = posY;
	this->direction = stairDirection;
}

Stairs::~Stairs(){}

void Stairs::Render()
{
	/*if (direction == 1) 
	{
		animationSet->at(STAIRS_RIGHTWAY)->Render(-direction, posX, posY);
	}
	else
	{
		animationSet->at(STAIRS_LEFTWAY)->Render(-direction, posX, posY);
	}*/
	RenderBoundingBox();
}

void Stairs::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX;
	t = posY;
	r = posX + STAIRS_BBOX_WIDTH;
	b = posY + STAIRS_BBOX_HEIGHT;
}
