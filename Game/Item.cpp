#include "Item.h"

Item::Item() 
{
	isDone = false;
	timeDisplayed = 0;
	timeDisplayMax = 0;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = 0;
}

Item::~Item(){}

void Item::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	//thoat khoi tinh trang doi
	timeDelayDisplayed += dt;
	if (timeDelayDisplayed < timeDelayDisplayMax)
	{
		return;
	}
	timeDisplayed += dt;
	if (timeDisplayed >= timeDisplayMax)	//xong trach nhiem
	{
		isDone = true;
		return;
	}

	Entity::Update(dt);

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
			vY = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void Item::Render()
{
	//Dung ra thi khi het delay moi tao item chu khong phai tao roi nhung het delay moi ve
	if (timeDelayDisplayed < timeDelayDisplayMax)
		return;
	if (isDone)
		return;

	sprite->Draw(posX, posY);

	RenderBoundingBox();
}

void Item::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDone) 
	{
		left = posX;
		top = posY;
		right = posX + texture->getFrameWidth();
		bottom = posY + texture->getFrameHeight();
	}
}
