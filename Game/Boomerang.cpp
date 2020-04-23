#include "Boomerang.h"

Boomerang::Boomerang(LPGAMEENTITY owner)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BOOMERANG));
	tag = EntityType::BOOMERANG;
	ownerPosX = 0;
	timeDelayed = 0;
	timeDelayMax = MAX_BOOMERANG_DELAY;

	this->owner = owner;
}

Boomerang::~Boomerang() {}

void Boomerang::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	
	Weapon::Update(dt);
	posX += dx;

	if (ownerDirection == direction)	//state nem' di
	{
		if (abs(ownerPosX - this->posX) >= BOOMERANG_MAX_DISTANCE)
		{
			direction *= -1;
			vX *= -1;
		}
	}	
	else	//state quay ve
	{
		if (IsCollidingObject(owner) || abs(ownerPosX - this->posX) >= 1.5*BOOMERANG_MAX_DISTANCE)	//cham simon
		{
			isDone = true;
		}
	}
}

void Boomerang::Attack(float posX, float posY, int direction)
{
	Weapon::Attack(posX, posY, direction);
	ownerPosX = posX;
	ownerDirection = direction;
	this->posY -= 8;	//Fit Simon Hand
	vX = BOOMERANG_SPEED_X * this->direction;
}

void Boomerang::Render()
{
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	if (isDone)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();

}

void Boomerang::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + BOOMERANG_BBOX_WIDTH;
	bottom = posY + BOOMERANG_BBOX_HEIGHT;
}