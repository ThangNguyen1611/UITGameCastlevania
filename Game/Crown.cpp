#include "Crown.h"

Crown::Crown(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CROWN));
	tag = EntityType::CROWN;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(CROWN_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = CROWN_TIMEDELAYMAX;
	isShowDone = false;
}

Crown::~Crown() {}

void Crown::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	//Do kha nang moc. tu dat' len nen khong the dung lai item::update

	if (isDone) return;
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

	if (isShowDone)
	{
		vY = CROWN_GRAVITY;
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
	else
	{
		vY = -CROWN_PUSHUP_SPEED;
		posY += dy;
		if (posY <= 409)
		{
			isShowDone = true;
		}
	}
}
