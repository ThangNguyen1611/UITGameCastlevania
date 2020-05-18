#include "Cross.h"

Cross::Cross(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CROSS));
	tag = EntityType::CROSS;

	this->posX = posX;
	this->posY = posY;

	vY = CROSS_GRAVITY;
	displayTimer = new Timer(CROSS_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = CROSS_TIMEDELAYMAX;
}

Cross::~Cross() {}