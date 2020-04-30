#include "DarkenBat.h"
#include <math.h>
#define PI 3.141562535898

DarkenBat::DarkenBat(float posX, float posY, int directionX, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_DARKENBAT));
	tag = EntityType::DARKENBAT;

	this->posX = posX;
	this->posY = posY;
	this->tempY = posY;
	this->direction = directionX;
	directionY = 1;

	this->SetState(DARKBAT_STATE_INACTIVE);

	health = 1;
	isDead = false;
	targetDetected = false;
	this->target = target;
}

DarkenBat::~DarkenBat(){}

void DarkenBat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 0)
	{
		SetState(DARKBAT_STATE_DIE);
		return;
	}

	if (target != NULL)
	{
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= 200)
		{
			targetDetected = true;
			SetState(DARKBAT_STATE_FLYING);
		}
	}

	if (vX != 0)
	{
		//posY = 60 * sin(0.3 * posX * PI / 180) + tempY;
		//posY = ((-1 * pow(posX, 2)) / 125) + (1057 * posX / 288) - 214;
		//posY = ((-23 * pow(posX, 2)) / 2702) + (123 * posX / 32) - 227;
		if (posY - tempY >= DARKBAT_AMPLITUDE_HORIZONTAL)
			directionY = -1;
		else if(tempY - posY >= DARKBAT_AMPLITUDE_HORIZONTAL)
			directionY = 1;

		vY += DARKBAT_FLYING_SPEED_Y * directionY;
	}

	Entity::Update(dt);
	posX += dx;
	posY += dy;

}

void DarkenBat::Render()
{
	if (isDead)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();
}


void DarkenBat::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case DARKBAT_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case DARKBAT_STATE_FLYING:
		vX = DARKBAT_FLYING_SPEED_X * direction;
		directionY = 1;
		break;
	case DARKBAT_STATE_INACTIVE:
		vX = 0;
		vY = 0;
		break;
	}
}

void DarkenBat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead) 
	{
		l = posX;
		t = posY;
		r = posX + DARKBAT_BBOX_WIDTH;
		b = posY + DARKBAT_BBOX_HEIGHT;
	}
}