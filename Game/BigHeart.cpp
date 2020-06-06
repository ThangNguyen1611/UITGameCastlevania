#include "BigHeart.h"

BigHeart::BigHeart(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BIGHEART));
	tag = EntityType::BIGHEART;

	this->posX = posX;
	this->posY = posY;
	
	displayTimer = new Timer(BIGHEART_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = BIGHEART_DELAY;
}

BigHeart::~BigHeart(){}