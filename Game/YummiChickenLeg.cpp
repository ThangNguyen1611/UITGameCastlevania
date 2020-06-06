#include "YummiChickenLeg.h"

YummiChickenLeg::YummiChickenLeg(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CHICKENLEG));
	tag = EntityType::YUMMICHICKENLEG;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(CHICKEN_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = CHICKEN_DELAY;
}

YummiChickenLeg::~YummiChickenLeg() {}