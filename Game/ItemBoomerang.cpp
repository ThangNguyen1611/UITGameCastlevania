#include "ItemBoomerang.h"

ItemBoomerang::ItemBoomerang(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMBMR));
	tag = EntityType::ITEMBOOMERANG;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMBOOMERANG_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMBOOMERANG_DELAY;
}

ItemBoomerang::~ItemBoomerang() {}