#include "Pokeball.h"

Pokeball::Pokeball()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_POKEBALL));
	tag = EntityType::POKEBALL;
	timeDelayed = 0;
	timeDelayMax = PKB_DELAY;
	damage = PKB_DAMAGE;
}

Pokeball::~Pokeball() {}

void Pokeball::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		tempY = posY;
		isReceivedPos = false;
		return;
	}

	if (tempY - posY >= PKB_MAX_HEIGHT)
		directionY = 1;

	if (posY > BOTTOM_SCREEN) //SCREENHEIGHT - BOARDHEIGHT
		isDone = true;

	vY += PKB_SPEED_Y * directionY;		// += bring the parabol-shape fly

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

		if ((nx != 0 || ny != 0) && animationSet->at(0)->GetCurrentFrame() == 10)
		{
			if (!isOpened)
			{
				openTimer->Start();
				isOpened = true;
			}
		}
		if (nx != 0 && ny == 0)
		{
			direction *= -1;
			vX *= -1;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	if (isOpened && openTimer->IsTimeUp())
	{
		openTimer->Reset();
		isOpened = false;
		isDone = true;
	}
}

void Pokeball::Attack(float posX, int direction)
{
	Weapon::Attack(posX, direction);
	this->posY -= WEAPON_ARTICULATED_POS_Y;	//Fit Simon Hand
	vX = PKB_SPEED_X * this->direction;
	directionY = -1;
	vY = 0;
	isOpened = false;
}

void Pokeball::Render()
{
	if (timeDelayed <= timeDelayMax)
		return;
	if (isDone)
		return;

	if(!isOpened)
		animationSet->at(0)->Render(direction, posX, posY);
	else
		animationSet->at(1)->Render(direction, posX, posY);

	RenderBoundingBox();

}

void Pokeball::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + PKB_BBOX_WIDTH;
	bottom = posY + PKB_BBOX_HEIGHT;
}

