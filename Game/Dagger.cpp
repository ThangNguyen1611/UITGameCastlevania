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

void Dagger::Attack(float posX, float posY, int direction)
{
	Weapon::Attack(posX, posY, direction);
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

bool Dagger::CheckIsOutCamera(float posX)
{
	if (vX > 0)	//Walking Right
	{
		if (this->posX - posX >= (SCREEN_WIDTH / 2))
			return true;
	}
	else if (vX < 0)
	{
		if (posX - this->posX >= (SCREEN_WIDTH / 2))
			return true;
	}
	return false;
}
