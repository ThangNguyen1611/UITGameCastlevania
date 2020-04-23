#include "YummiChickenLeg.h"

YummiChickenLeg::YummiChickenLeg(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CHICKENLEG));
	tag = EntityType::YUMMICHICKENLEG;

	this->posX = posX;
	this->posY = posY;

	vY = CHICKEN_GRAVITY;
	displayTimer = new Timer(CHICKEN_TIMEDISPLAYMAX);
	displayTimer->Start();
}

YummiChickenLeg::~YummiChickenLeg() {}