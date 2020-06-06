#include "Drug.h"

Drug::Drug(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_INVIPOTION));
	tag = EntityType::INVIPOTION;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(DRUG_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = DRUG_DELAY;
}

Drug::~Drug() {}