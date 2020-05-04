#include "Hunchman.h"

Hunchman::Hunchman(float posX, float posY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_HUNCHMAN));
	tag = EntityType::HUNCHMAN;

	this->posX = posX;
	this->posY = posY;
	this->target = target;

	SetState(HUNCHMAN_STATE_ACTIVE);

	health = 1;
	isDead = false;

	targetDetected = false;
	activated = false;
	targetSwitchDirection = false;
}

Hunchman::~Hunchman() {}

void Hunchman::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
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
		else
			if (ny == -1)
				vY = 0;
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
		vX = HUNCHMAN_WALKING_SPEED * direction;
	}

	if (!activated)
	{
		if (target != NULL)
		{
			if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= 300)
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
		if (target->GetPosX() < posX) direction = -1;
		else direction = 1;
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
		l = posX - 15;
		t = posY;
		r = posX + HUNCHMAN_BBOX_WIDTH;
		b = posY + HUNCHMAN_BBOX_HEIGHT;
	}
}
