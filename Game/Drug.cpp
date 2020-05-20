#include "Drug.h"

Drug::Drug(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_INVIPOTION));
	tag = EntityType::INVIPOTION;

	this->posX = posX;
	this->posY = posY;

	vY = DRUG_GRAVITY;
	displayTimer = new Timer(DRUG_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = DRUG_TIMEDELAYMAX;
}

Drug::~Drug() {}