#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_MOVINGFLATFORM));
	tag = EntityType::MOVINGPLATFORM;

	this->posX = posX;
	this->posY = posY;
	direction = 1;
	vX += PLAT_FLOATING_SPEED_X;
}

MovingPlatform::~MovingPlatform() {}

void MovingPlatform::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	Entity::Update(dt);

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
			direction *= -1;
			vX *= -1;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void MovingPlatform::Render()
{
	animationSet->at(0)->Render(-direction, posX, posY);
	RenderBoundingBox();
}

void MovingPlatform::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX - PLAT_BBOX_WIDTH / 4;
	t = posY;
	r = posX + PLAT_BBOX_WIDTH;
	b = posY + PLAT_BBOX_HEIGHT;
}

