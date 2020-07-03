#include "Bat.h"
#include <math.h>
#define PI 3.141562535898

Bat::Bat(float posX, float posY, int direction) 
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BAT));
	tag = EntityType::BAT;

	this->posX = posX;
	this->posY = posY;
	tempY = posY;
	this->direction = direction;
	directionY = 1;

	this->SetState(BAT_STATE_FLYING);

	health = BAT_MAXHEALTH;
	isDead = false;
}

Bat::~Bat(){}

void Bat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 0 || posX > SCREEN_WIDTH * 2.85f)
	{
		SetState(BAT_STATE_DIE);
		return;
	}
	
	//2 optional to FLY

	//zigzag one
	/*if (posY - tempY >= BAT_AMPLITUDE_HORIZONTAL)
		directionY = -1;
	else if(tempY - posY >= BAT_AMPLITUDE_HORIZONTAL)
		directionY = 1;

	vY = BAT_FLYING_SPEED_Y * directionY;*/

	//sin one
	posY = 30 * sin(1.5*posX*PI / 180) + tempY;

	Entity::Update(dt);
	posX += dx;
	posY += dy;

}

void Bat::Render() 
{
	if (isDead)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();
}

void Bat::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case BAT_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case BAT_STATE_FLYING:
		vX = BAT_FLYING_SPEED_X * direction;
		break;
	}
}

void Bat::GetBoundingBox(float &l, float &t, float &r, float &b) 
{
	//not clean
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + BAT_BBOX_WIDTH;
		b = posY + BAT_BBOX_HEIGHT;
	}
}
