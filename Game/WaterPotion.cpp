#include "WaterPotion.h"

WaterPotion::WaterPotion()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_WATERPOTION));
	tag = EntityType::WATERPOTION;
	timeDelayed = 0;
	timeDelayMax = WATPOT_DELAY;

	damage = WATPOT_DAMAGE;
}

WaterPotion::~WaterPotion() {}

void WaterPotion::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		tempY = posY;
		isReceivedPos = false;
		return;
	}

	if (state == WATPOT_STATE_BURN && burnDuration->IsTimeUp())
	{
		state = WATPOT_STATE_POT;
		isDone = true;
		burnDuration->Reset();
	}

	if (state == WATPOT_STATE_POT)
	{
		if (tempY - posY >= WATPOT_MAX_HEIGHT)
			directionY = 1;

		vY += WATPOT_SPEED_Y * directionY;		// += bring the parabol-shape fly
	}

	Weapon::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> listObjMayCollide;			
	coEvents.clear();
	listObjMayCollide.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() != EntityType::TORCH &&
			coObjects->at(i)->GetType() != EntityType::STAIRS&&
			coObjects->at(i)->GetType() != EntityType::CANDLE&&
			coObjects->at(i)->GetType() != EntityType::BUSH)
			listObjMayCollide.push_back(coObjects->at(i));

	CalcPotentialCollisions(&listObjMayCollide, coEvents);

	if (coEvents.size() == 0)
	{
		posX += dx;
		posY += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		posX += min_tx * dx + nx * 0.1f;
		posY += min_ty * dy + ny * 0.1f;

		if (nx != 0 || ny != 0)
		{
			posY += WATPOT_LOWER_DISTANCE;	//Burn a little bit lower to make sure do damage
			SetState(WATPOT_STATE_BURN);
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void WaterPotion::Attack(float posX, int direction)
{
	Weapon::Attack(posX, direction);
	this->posY -= WEAPON_ARTICULATED_POS_Y;	//Fit Simon Hand
	vX = WATPOT_SPEED_X * this->direction;
	directionY = -1;
	state = WATPOT_STATE_POT;
}

void WaterPotion::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case WATPOT_STATE_BURN:
		burnDuration->Start();
		vX = 0;
		vY = 0;
		break;
	}
}

void WaterPotion::Render()
{
	if (timeDelayed <= timeDelayMax)
		return;
	if (isDone)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();

}

void WaterPotion::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + WATPOT_BBOX_WIDTH;
	bottom = posY + WATPOT_BBOX_HEIGHT;
}

bool WaterPotion::IsCollidingObject(Entity* Obj)
{
	if (animationSet->at(WATPOT_STATE_BURN)->GetCurrentFrame() == 1)
		return Weapon::IsCollidingObject(Obj);

	return false;
}