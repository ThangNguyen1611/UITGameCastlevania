#include "Axe.h"

Axe::Axe()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_AXE));
	tag = EntityType::AXE;
	timeDelayed = 0;
	timeDelayMax = MAX_AXE_DELAY;
}

Axe::~Axe() {}

void Axe::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		tempY = posY;
		isReceivedPos = false;
		return;
	}

	if (tempY - posY >= AXE_MAX_DISTANCE_HEIGHT)
		directionY = 1;
	/*else if (posY - tempY >= 1)
		isDone = true;*/

	if (posY > 441) //SCREENHEIGHT - BOARDHEIGHT
		isDone = true;

	vY += AXE_SPEED_Y * directionY;		// += bring the parabol-shape fly

	Weapon::Update(dt);
	posX += dx;
	posY += dy;

}

void Axe::Attack(float posX, int direction)
{
	Weapon::Attack(posX, direction);
	this->posY -= 8;	//Fit Simon Hand
	vX = AXE_SPEED_X * this->direction;
	directionY = -1;
	vY = 0;
}

void Axe::Render()
{
	if (timeDelayed <= timeDelayMax)
		return;
	if (isDone)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();

}

void Axe::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + AXE_BBOX_WIDTH;
	bottom = posY + AXE_BBOX_HEIGHT;
}

