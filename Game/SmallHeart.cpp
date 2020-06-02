#include "SmallHeart.h"

SmallHeart::SmallHeart(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_SMALLHEART));
	tag = EntityType::SMALLHEART;

	this->posX = posX;
	this->posY = posY;
	tempX = posX;

	displayTimer = new Timer(SMALLHEART_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = SMALLHEART_DELAY;
	//Dat vX o day de vi kh co state va co the dung yen khi gap mat dat
	vX = SMALLHEART_SPEED_X * direction;
}

SmallHeart::~SmallHeart(){}

void SmallHeart::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (isDone) return;
	/*if (!finishedDelay && delayTimer->IsTimeUp())
	{
		displayTimer->Start();
		finishedDelay = true;
	}*/
	delayStart += dt;
	if (delayStart <= delayLimit)
	{
		return;
	}
	if (!isDone && displayTimer->IsTimeUp())
	{
		isDone = true;
	}

	if (posX - tempX >= SMALLHEART_AMPLITUDE_VERTICAL)
	{
		direction *= -1;
		vX *= -1;
	}
	else if (tempX - posX >= SMALLHEART_AMPLITUDE_VERTICAL)
	{
		direction *= -1;
		vX *= -1;
	}

	Entity::Update(dt);
	vY = SMALLHEART_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> bricks;

	coEvents.clear();
	bricks.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == EntityType::BRICK ||
			coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
			bricks.push_back(coObjects->at(i));

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

		if (ny == -1) 
		{
			vX = 0;
			vY = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
