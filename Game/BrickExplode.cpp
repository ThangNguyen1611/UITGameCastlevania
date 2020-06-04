#include "BrickExplode.h"

BrickExplode::BrickExplode(float posX, float posY, int type)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BRICKEXPLODE));
	this->posX = posX;
	this->posY = posY;
	tempY = posY;
	isDone = false;
	this->type = type;

	directionY = -1;
}

BrickExplode::~BrickExplode() {}

void BrickExplode::Update(DWORD dt)
{
	if (isDone)	return;
	if (posY > BOTTOM_SCREEN) isDone = true;

	switch (type)
	{
	case EXPLODE_TYPE1:
		direction = -1;
		if (tempY - posY >= EXPLODE_MAXHEIGHT_TYPE1)
			directionY = 1;
		vX = EXPLODE_SPEED_X_TYPE1 * direction;
		vY += EXPLODE_SPEED_Y_TYPE1 * directionY;		// += bring the parabol-shape fly
		break;
	case EXPLODE_TYPE2:
		direction = -1;
		if (tempY - posY >= EXPLODE_MAXHEIGHT_TYPE2)
			directionY = 1;
		vX = EXPLODE_SPEED_X_TYPE2 * direction;
		vY += EXPLODE_SPEED_Y_TYPE2 * directionY;		// += bring the parabol-shape fly
		break;
	case EXPLODE_TYPE3:
		direction = 1;
		if (tempY - posY >= EXPLODE_MAXHEIGHT_TYPE3)
			directionY = 1;
		vX = EXPLODE_SPEED_X_TYPE3 * direction;
		vY += EXPLODE_SPEED_Y_TYPE3 * directionY;		// += bring the parabol-shape fly
		break;
	case EXPLODE_TYPE4:
		direction = 1;
		if (tempY - posY >= EXPLODE_MAXHEIGHT_TYPE4)
			directionY = 1;
		vX = EXPLODE_SPEED_X_TYPE4 * direction;
		vY += EXPLODE_SPEED_Y_TYPE4 * directionY;		// += bring the parabol-shape fly
		break;
	default:
		break;
	}

	posX += vX * dt;
	posY += vY * dt;
}

void BrickExplode::Render()
{
	if (!isDone)
		if (type == EXPLODE_TYPE1 || type == EXPLODE_TYPE3)
			animationSet->at(0)->Render(-1, posX, posY);
		else
			animationSet->at(0)->Render(1, posX, posY);
}
