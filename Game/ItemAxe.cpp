#include "ItemAxe.h"

ItemAxe::ItemAxe(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMAXE));
	tag = EntityType::ITEMAXE;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMAXE_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMAXE_DELAY;
}

ItemAxe::~ItemAxe() {}