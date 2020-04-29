#include "Dagger.h"

Dagger::Dagger()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_DAGGER));
	tag = EntityType::DAGGER;
	ownerPosX = 0;
	timeDelayed = 0;
	timeDelayMax = MAX_DAGGER_DELAY;
}

Dagger::~Dagger(){}

void Dagger::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		isReceivedPos = false;
		return;
	}
	if (CheckIsOutCamera(ownerPosX))
	{
		isDone = true;
		return;
	}
	Weapon::Update(dt);
	posX += dx;
}

void Dagger::Attack(float posX, int direction)
{
	Weapon::Attack(posX, direction);
	ownerPosX = posX;
	this->posY -= 8;	//Fit Simon Hand
	vX = DAGGER_SPEED_X * this->direction;
}

void Dagger::Render()
{
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	if (isDone)
		return;

	animationSet->at(0)->Render(-direction, posX, posY);

	RenderBoundingBox();
	
}

void Dagger::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + DAGGER_BBOX_WIDTH;
	bottom = posY + DAGGER_BBOX_HEIGHT;
}


