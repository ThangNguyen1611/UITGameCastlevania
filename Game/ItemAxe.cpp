#include "ItemAxe.h"

ItemAxe::ItemAxe(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMAXE));
	tag = EntityType::ITEMAXE;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMAXE_GRAVITY;
	displayTimer = new Timer(ITEMAXE_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = ITEMAXE_TIMEDELAYMAX;
}

ItemAxe::~ItemAxe() {}