#include "Hunchman.h"
#include "Player.h"
#include "Brick.h"

Hunchman::Hunchman(float posX, float posY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_HUNCHMAN));
	tag = EntityType::HUNCHMAN;	//BEST BOY CUA NAM ((:

	this->posX = posX;
	this->posY = posY;
	this->target = target;

	SetState(HUNCHMAN_STATE_ACTIVE);

	health = HUNCHMAN_MAXHEALTH;
	isDead = false;

	targetDetected = false;
	activated = false;
	targetSwitchDirection = false;
	isJumping = false;
	triggerJump = false;
	triggerWaitingJump = false;
}

Hunchman::~Hunchman() {}

void Hunchman::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 5 || posX > SCREEN_WIDTH * 2.85f || posY > BOTTOM_SCREEN ||
		(activated && abs(this->posX - target->GetPosX()) >= SCREEN_WIDTH * 0.55))
	{
		SetState(HUNCHMAN_STATE_DIE);
		return;
	}

	Entity::Update(dt);
	
	vY += HUNCHMAN_GRAVITY * dt;

#pragma region Collision Logic
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK ||
			coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
			bricks.push_back(coObjects->at(i));

	// turn off collision when die 
	if (state != HUNCHMAN_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		posX += dx;
		posY += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		posX += min_tx * dx + nx * 0.1f;
		posY += min_ty * dy + ny * 0.1f;

		if (nx != 0 && ny == 0)
		{
			if (target->GetPosX() < posX && direction == 1 || 
				target->GetPosX() > posX && direction == -1)		//Wrong Chase-Direction
				TurnAround();
		}
		if (ny == -1)
		{
			vY = 0;
			isJumping = false;
			if (!triggerWaitingJump)
			{
				waitingJumpTimer->Start();
				triggerWaitingJump = true;
			}
		}
		if (!triggerJump && waitingJumpTimer->IsTimeUp())
		{
			triggerJump = true;
			waitingJumpTimer->Reset();
			triggerWaitingJump = false;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
#pragma endregion
#pragma region Activate Logic
	if (!activated)
	{
		vX = 0;
	}
	else
	{
		if(!isJumping)
			vX = 0;
#pragma region Jump Logic
		if (triggerJump)
		{
			if (abs(target->GetPosX() - posX) <= HUNCHMAN_CLOSE_TARGET_RANGE && 
				posY >= HUNCHMAN_MAX_HEIGHT_HIGHJUMP &&
				rand() % 100 <= 66 &&
				!IsObstacleAbove(coObjects))	//Co the gan nhung khong nhay cao
				Jump(HUNCHMAN_HIGHJUMP_SPEED_X, HUNCHMAN_HIGHJUMP_SPEED_Y);
			else 
				Jump(HUNCHMAN_JUMP_SPEED_X, HUNCHMAN_JUMP_SPEED_Y);
		}
#pragma endregion

		//LongJump aka Dodge Logic
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= HUNCHMAN_SIGHT_DODGE_RANGE && //Trong tam nhin 3 o gach cua mob
			target->GetDirection() != this->direction &&	//Doi dien nhau -> Nguy co chet vi bi danh
			!target->IsUnsighted() &&
			(target->GetAnimationSet()->at(PLAYER_STATE_ATTACKING)->GetCurrentFrame() == 0 ||	//Frame dau cua attack
			target->GetAnimationSet()->at(PLAYER_STATE_SITTING_ATTACK)->GetCurrentFrame() == 0 ||
			target->GetAnimationSet()->at(PLAYER_STATE_SUPWEAPON_ATTACK)->GetCurrentFrame() == 0 ||
			target->GetAnimationSet()->at(PLAYER_STATE_SUPWEAPON_SIT_ATTACK)->GetCurrentFrame() == 0))
		{
			if(rand() % 100 <= 50 && posY >= HUNCHMAN_MAX_HEIGHT_HIGHJUMP)	//Co 50% nhay ne
				Jump(HUNCHMAN_DODGEJUMP_SPEED_X, HUNCHMAN_DODGEJUMP_SPEED_Y);
		}
	}

	if (!activated)
	{
		if (target != NULL)
		{
			if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= HUNCHMAN_SIGHT_RANGE && target->GetState() != 0 && !target->IsUnsighted())
			{
				if (!targetDetected)
				{
					readyTimer->Start();
					targetDetected = true;
				}
			}
		}
	}

	if (targetDetected && readyTimer->IsTimeUp())
	{
		readyTimer->Reset();
		targetDetected = false;
		activated = true;
		Jump(HUNCHMAN_HIGHJUMP_SPEED_X, HUNCHMAN_HIGHJUMP_SPEED_Y);
	}
#pragma endregion
#pragma region Switch Direction React
	if (target != NULL)
	{
		if (target->GetPosX() < posX && direction == 1 || 
			target->GetPosX() > posX && direction == -1)		//Wrong Chase-Direction
		{
			if (!targetSwitchDirection)
			{
				reactTimer->Start();
				targetSwitchDirection = true;
			}
		}
	}

	if (targetSwitchDirection && reactTimer->IsTimeUp())
	{
		if (!target->IsUnsighted())
		{
			if (target->GetPosX() < posX) direction = -1;
			else direction = 1;
		}
		else
		{
			int random = rand() % 100;
			if (random <= 50)
				direction *= -1;
		}
		reactTimer->Reset();
		targetSwitchDirection = false;
	}
#pragma endregion
}

void Hunchman::TurnAround()
{
	direction *= -1;
	vX *= -1;
}

void Hunchman::Jump(float vX, float vY)
{
	isJumping = true;
	this->vX = vX * direction;
	this->vY = -vY;
	triggerJump = false;
}

bool Hunchman::IsObstacleAbove(vector<LPGAMEENTITY> *coObjects)
{
	float tempPosY = posY;
	for (tempPosY; tempPosY > posY - HUNCHMAN_JUMP_DISTANCE; tempPosY--)
		for (UINT i = 0; i < coObjects->size(); i++)
			if (coObjects->at(i)->GetPosY() <= tempPosY && 
				coObjects->at(i)->GetPosX() >= posX - BRICK_BBOX_WIDTH * 2 && 
				coObjects->at(i)->GetPosX() <= posX + BRICK_BBOX_WIDTH * 2)
				if (coObjects->at(i)->GetType() == EntityType::BRICK || coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
					return true;
	return false;
}

void Hunchman::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();
}

void Hunchman::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case HUNCHMAN_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	}
}

void Hunchman::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead)
	{
		l = posX - HUNCHMAN_BBOX_WIDTH / 2;
		t = posY;
		r = posX + HUNCHMAN_BBOX_WIDTH;
		b = posY + HUNCHMAN_BBOX_HEIGHT;
	}
}
