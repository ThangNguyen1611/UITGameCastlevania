#include "DarkenBat.h"
#include "Player.h"
#include <math.h>
#define PI 3.141562535898

DarkenBat::DarkenBat(float posX, float posY, int directionX, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_DARKENBAT));
	tag = EntityType::DARKENBAT;

	this->posX = posX;
	this->firstPosX = posX;
	this->posY = posY;
	this->tempY = posY;
	this->direction = directionX;
	directionY = 1;

	this->SetState(DARKBAT_STATE_INACTIVE);

	health = DARKBAT_MAXHEALTH;
	isDead = false;
	this->target = target;
	isDonePhase1 = false;
}

DarkenBat::~DarkenBat(){}

void DarkenBat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 5 || posX > SCREEN_WIDTH * 2.85f)
	{
		SetState(DARKBAT_STATE_DIE);
		return;
	}

	if (target != NULL)
	{
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= DARKBAT_SIGHT_RANGE && !target->IsUnsighted())
		{
			SetState(DARKBAT_STATE_FLYING);
		}
	}

	if (!isDonePhase1)
	{
		if (vX != 0)
		{
			if (posY - tempY >= DARKBAT_AMPLITUDE_HORIZONTAL)
				directionY = -1;
			else if (tempY - posY >= DARKBAT_AMPLITUDE_HORIZONTAL)
				directionY = 1;

			vY += DARKBAT_FLYING_SPEED_Y * directionY;
		}
		if (posX > DARKBAT_DISTANCE_END_PHASE1 + firstPosX)	//Bat co song am nen tang hinh vo dung :D
		{
			isDonePhase1 = true;
		}
	}
	if (isDonePhase1)
	{
		vY = 0;
		/*D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
		pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, DARKBAT_FLYING_SPEED_PHASE2);
		posX = pos.x;
		posY = pos.y;
		if (target->GetPosX() < posX)
			direction = -1;
		else
			direction = 1;*/
	}

	Entity::Update(dt);
	//if (!isDonePhase1) 
	//{
		posX += dx;
		posY += dy;
	//}

	SelfDestroy();
}

void DarkenBat::SelfDestroy()
{
	if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= DARKBAT_CLOSED_RANGE)
	{
		Player* pl = dynamic_cast<Player*>(target);
		if (!pl->IsImmortaling())
		{
			pl->AddHealth(-DARKBAT_DAMAGE);
			pl->StartHurtingTimer();
			pl->StartImmortalingTimer();
			pl->SetImmortal(true);
			pl->SetState(PLAYER_STATE_HURTING);
		}
		SetState(DARKBAT_STATE_DIE);
		return;
	}
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
		health = 0;
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