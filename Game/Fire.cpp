#include "Fire.h"

Fire::Fire(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_FIREEFFECT));
	this->posX = posX;
	this->posY = posY;
	isDone = false;
	animationSet->at(0)->StartAnimation();
}

Fire::~Fire() {}

void Fire::Update(DWORD dt)
{
	if (isDone)	//Khong bo vao Effect::Update do khong return duoc Update o day
	{
		return;
	}
	if (animationSet->at(0)->IsRenderOver(FIRE_BURN_DISPLAY*2))
	{
		isDone = true;
	}
}
