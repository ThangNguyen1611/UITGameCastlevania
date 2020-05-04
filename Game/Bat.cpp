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

	health = 1;
	isDead = false;
}

Bat::~Bat(){}

void Bat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 0 || posX > SCREEN_WIDTH * 2)
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

#pragma region Past
	//Entity* target;
	////Player is the first unit of vector
	//target = coObjects->at(0);
	//if (!target->IsDeadYet() && !isDead) {
	//	//AI (testing - not neccesary)
	//	D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
	//	//speed nay dc define cho vX (pos += vX * dt) nen khi muon dung cho pos phai nhan voi 1 so tuong duong dt
	//	pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, BAT_FLYING_SPEED * 10);
	//	posX = pos.x;
	//	posY = pos.y;
	//}
	//Entity::Update(dt);

#pragma endregion
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
