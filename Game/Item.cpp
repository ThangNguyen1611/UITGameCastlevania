#include "Item.h"

Item::Item() 
{
	isDone = false;
	//finishedDelay = false;
	delayStart = 0;
}

Item::~Item(){}

void Item::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
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

	Entity::Update(dt);
	vY = ITEM_GRAVITY;

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

	if (coEvents.size() == 0)
	{
		posY += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		posX += min_tx * dx + nx * 0.1f;
		posY += min_ty * dy + ny * 0.1f;

		if (ny == -1)
			vY = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void Item::Render()
{
	if (isDone || delayStart <= delayLimit)
		return;

	animationSet->at(0)->Render(-direction, posX, posY);

	RenderBoundingBox();
}

void Item::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone) 
	{
		left = posX;
		top = posY;
		right = posX + animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite()->GetFrameWidth();
		bottom = posY + animationSet->at(0)->GetAnimationCurrentFrame(0)->GetSprite()->GetFrameHeight();
	}
}
