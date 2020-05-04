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
}

Ghost::~Ghost() {}

void Ghost::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		SetState(GHOST_STATE_DIE);
		return;
	}
	D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
	pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, GHOST_FLYING_SPEED);
	posX = pos.x;
	posY = pos.y;
	if (target->GetPosX() < posX)
		direction = 1;
	else
		direction = -1;
	
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
