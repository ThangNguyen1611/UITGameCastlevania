#include "Ghost.h"

Ghost::Ghost(float posX, float posY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_GHOST));
	tag = EntityType::GHOST;

	this->posX = posX;
	this->posY = posY;
	this->target = target;

	this->SetState(GHOST_STATE_FLYING);

	health = 2;
	isDead = false;

	currentTotalTime = 2000;
}

Ghost::~Ghost() {}

void Ghost::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 5 || posX > SCREEN_WIDTH * 2.85f)// || target->GetState() == 0)
	{
		SetState(GHOST_STATE_DIE);
		return;
	}
	if (!target->IsUnsighted())
	{
		D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
		pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, GHOST_FLYING_SPEED);
		posX = pos.x;
		posY = pos.y;
		if (target->GetPosX() < posX)
			direction = 1;
		else
			direction = -1;
	}
	else	//Random targetPos Logic
	{
		D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
		currentTotalTime += dt;
		if (currentTotalTime >= GHOST_RANDOM_TIMECYCLE)
		{
			randomPosX = rand() % 100 + 150; //	100->150
			randomPosY = rand() % 70 + 50; //	50->70
			int randomDirectionX = rand() % 100;
			int randomDirectionY = rand() % 100;
			if (randomDirectionX <= 50)
				direction = -1;
			else
				direction = 1;
			if (randomDirectionY <= 50)
				dirY = -1;
			else
				dirY = 1;
			currentTotalTime = 0;
		}
		if ((posY - randomPosY * dirY) > 440 || (posY - randomPosY * dirY) < 0) 
			dirY *= -1;
		pos += RadialMovement(D3DXVECTOR2(posX - randomPosX * direction, posY - randomPosY * dirY), pos, GHOST_FLYING_SPEED);
		//Dau tru trong cong thuc rat QUAN TRONG //Dau tru trong cong thuc rat QUAN TRONG //Dau tru trong cong thuc rat QUAN TRONG
		posX = pos.x;
		posY = pos.y;
	}
	
	Entity::Update(dt);
}

void Ghost::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(-direction, posX, posY);

	RenderBoundingBox();
}

void Ghost::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case GHOST_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	}
}

void Ghost::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + GHOST_BBOX_WIDTH;
		b = posY + GHOST_BBOX_HEIGHT;
	}
}
