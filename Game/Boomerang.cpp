#include "Boomerang.h"

Boomerang::Boomerang(LPGAMEENTITY owner)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BOOMERANG));
	tag = EntityType::BOOMERANG;
	ownerPosX = 0;
	timeDelayed = 0;
	timeDelayMax = BOOMERANG_DELAY;

	this->owner = owner;
	isDidDamageTurn1 = false;
	isDidDamageTurn2 = false;

	damage = BOOMERANG_DAMAGE;
}

Boomerang::~Boomerang() {}

void Boomerang::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		isReceivedPos = false;
		return;
	}
	
	Weapon::Update(dt);
	posX += dx;

	if (ownerDirection == direction)	//state nem' di
	{
		if (abs(ownerPosX - this->posX) >= BOOMERANG_RANGE)
		{
			direction *= -1;
			vX *= -1;
		}
	}	
	else	//state quay ve
	{
		if (IsCollidingObject(owner) || abs(ownerPosX - this->posX) >= 1.5*BOOMERANG_RANGE)	//cham simon
		{
			isDone = true;
		}
	}
}

void Boomerang::Attack(float posX, int direction)
{
	Weapon::Attack(posX, direction);
	ownerPosX = posX;
	ownerDirection = direction;
	this->posY -= WEAPON_ARTICULATED_POS_Y;	//Fit Simon Hand
	vX = BOOMERANG_SPEED_X * this->direction;
	isDidDamageTurn1 = false;
	isDidDamageTurn2 = false;
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
