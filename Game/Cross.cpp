#include "Cross.h"

Cross::Cross(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CROSS));
	tag = EntityType::CROSS;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(CROSS_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = CROSS_DELAY;
}

Cross::~Cross() {}