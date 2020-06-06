#include "Skeleton.h"

Skeleton::Skeleton(float posX, float posY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_SKELETON));
	tag = EntityType::SKELETON;	

	this->posX = posX;
	this->posY = posY;
	this->target = target;

	SetState(SKELETON_STATE_ACTIVE);

	health = SKELETON_MAXHEALTH;
	isDead = false;

	targetDetected = false;
	activated = false;
	targetSwitchDirection = false;
	isJumping = false;
	triggerJump = false;

	mainWeapon = new Bone();
	mainWeaponAtDouble = new Bone();
	mainWeaponAtTriple = new Bone();
	triggerResetDelay = false;
}

Skeleton::~Skeleton() {}

void Skeleton::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 5 || posX > SCREEN_WIDTH * 2.85f || posY > BOTTOM_SCREEN || 
		(activated && abs(this->posX - target->GetPosX()) >= SCREEN_WIDTH * 0.55))
	{
		SetState(SKELETON_STATE_DIE);
		return;
	}

	Entity::Update(dt);

	vY += SKELETON_GRAVITY * dt;

	if (!triggerResetDelay)
	{
		mainWeapon->ResetDelay();
		mainWeaponAtDouble->ResetDelay();
		triggerResetDelay = true;
	}

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

	if (state != SKELETON_STATE_DIE)
		CalcPotentialCollisions(&bricks, coEvents);

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
		}

		if (coEvents.size() == 1)	//Ria Brick
			if (!isJumping)
				triggerJump = true;
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
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) >= SKELETON_SIGHT_CHASE_RANGE)
			vX = SKELETON_WALKING_SPEED_X * direction;
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= SKELETON_SIGHT_FEAR_RANGE)
			vX = -SKELETON_WALKING_SPEED_X * direction;

		if (triggerJump)
			Jump();
#pragma region Attack Logic
		if((rand() % 1000) < 50)
			if (!target->IsUnsighted())				//Khong thay target thi khong danh lung tung
			{
				Attack();
				if ((rand() % 100) < 50)
				{
					triggerDoubleAttack = true;
					doubleAttackDelayTimer->Start();
				}
			}
		if (triggerDoubleAttack && doubleAttackDelayTimer->IsTimeUp())
		{
			DoubleAttack();
			triggerDoubleAttack = false;
			doubleAttackDelayTimer->Reset();
			if ((rand() % 100) < 50)
			{
				triggerTripleAttack = true;
				tripleAttackDelayTimer->Start();
			}
		}
		if (triggerTripleAttack && tripleAttackDelayTimer->IsTimeUp())
		{
			TripleAttack();
			triggerTripleAttack = false;
			tripleAttackDelayTimer->Reset();
		}
#pragma endregion
	}

	if (!activated)
	{
		if (target != NULL)
		{
			if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= SKELETON_SIGHT_RANGE && target->GetState() != 0 && !target->IsUnsighted()) //Ngan xac simon kich hoat 
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
		Jump();
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

	if (!mainWeapon->GetIsDone())
	{
		if (!mainWeapon->GetIsReceivedPos())
		{
			mainWeapon->SetPosition(posX, posY);
			mainWeapon->SetIsReceivedPos(true);			//Chi nhan pos 1 lan sau khi het delay
		}
		mainWeapon->Update(dt, coObjects);
	}
	if (!mainWeaponAtDouble->GetIsDone())
	{
		if (!mainWeaponAtDouble->GetIsReceivedPos())
		{
			mainWeaponAtDouble->SetPosition(posX, posY);
			mainWeaponAtDouble->SetIsReceivedPos(true);			//Chi nhan pos 1 lan sau khi het delay
		}
		mainWeaponAtDouble->Update(dt, coObjects);
	}
	if (!mainWeaponAtTriple->GetIsDone())
	{
		if (!mainWeaponAtTriple->GetIsReceivedPos())
		{
			mainWeaponAtTriple->SetPosition(posX, posY);
			mainWeaponAtTriple->SetIsReceivedPos(true);			//Chi nhan pos 1 lan sau khi het delay
		}
		mainWeaponAtTriple->Update(dt, coObjects);
	}
}

void Skeleton::TurnAround()
{
	direction *= -1;
	vX *= -1;
}

void Skeleton::Jump()
{
	isJumping = true;
	vY = -SKELETON_JUMP_SPEED_Y;
	triggerJump = false;
}

void Skeleton::Attack()
{
	if (mainWeapon->GetIsDone())
	{
		mainWeapon->Attack(posX, direction);
	}
}

void Skeleton::DoubleAttack()
{
	if (mainWeaponAtDouble->GetIsDone())
	{
		mainWeaponAtDouble->Attack(posX, direction);
	}
}

void Skeleton::TripleAttack()
{
	if (mainWeaponAtTriple->GetIsDone())
	{
		mainWeaponAtTriple->Attack(posX, direction);
	}
}

void Skeleton::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();

	if (!mainWeapon->GetIsDone())
	{
		mainWeapon->Render();
	}
	if (!mainWeaponAtDouble->GetIsDone())
	{
		mainWeaponAtDouble->Render();
	}
	if (!mainWeaponAtTriple->GetIsDone())
	{
		mainWeaponAtTriple->Render();
	}
}

void Skeleton::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case SKELETON_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	}
}

void Skeleton::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead)
	{
		l = posX - SKELETON_BBOX_WIDTH / 2;
		t = posY;
		r = posX + SKELETON_BBOX_WIDTH;
		b = posY + SKELETON_BBOX_HEIGHT;
	}
}
