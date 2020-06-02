#include "Knight.h"

Knight::Knight(float posX, float posY, int directionX, float maxAmplitudeX)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_KNIGHT));
	tag = EntityType::KNIGHT;

	this->posX = posX;
	this->posY = posY;
	this->direction = directionX;
	startX = posX + 1;
	this->maxAmplitudeX = maxAmplitudeX;

	SetState(KNIGHT_STATE_WALKING);

	health = KNIGHT_MAXHEALTH;
	isDead = false;
	triggerHurting = false;

	randomTurnaround = false;
}

Knight::~Knight(){}

void Knight::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		SetState(KNIGHT_STATE_DIE);
		return;
	}

	if (triggerHurting && state != KNIGHT_STATE_HURTING)
	{
		hurtingTimer->Start();
		SetState(KNIGHT_STATE_HURTING);
		triggerHurting = false;
	}
	if (state == KNIGHT_STATE_HURTING && hurtingTimer->IsTimeUp())
	{
		hurtingTimer->Reset();
		SetState(KNIGHT_STATE_WALKING);
	}

	Entity::Update(dt);
	vY += KNIGHT_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;
	//Knight only collision with bricks
	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK ||
			coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
			bricks.push_back(coObjects->at(i));

	// turn off collision when die 
	if (state != KNIGHT_STATE_DIE)
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
			TurnAround();
		}
		else 
			if (ny == -1)
			vY = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	//Cham diem khoi dau hoac vuot qua bien do cho phep
	if (posX >= startX || posX <= startX - maxAmplitudeX)
	{
		TurnAround();
	}

	//Extension
	int random = rand() % 10000;	//The bigger random range, the more accurate
	if (random <= 50)
	{
		randomTurnaround = true;
		random = NULL;
	}

	if (randomTurnaround)
	{
		TurnAround();
		randomTurnaround = false;
	}

}

void Knight::TurnAround()
{
	direction *= -1;
	vX *= -1;
}

void Knight::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();
}

void Knight::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case KNIGHT_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case KNIGHT_STATE_WALKING:
		vX = KNIGHT_WALKING_SPEED_X * direction;
		break; 
	case KNIGHT_STATE_HURTING:
		vX = 0;
		break;
	}
}

void Knight::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead) 
	{
		l = posX - KNIGHT_ARTICULATOR_POS_X;
		t = posY;
		r = posX + KNIGHT_BBOX_WIDTH;
		b = posY + KNIGHT_BBOX_HEIGHT;
	}
}
