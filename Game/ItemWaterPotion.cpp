#include "ItemWaterPotion.h"

ItemWaterPotion::ItemWaterPotion(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMWATERPOTION));
	tag = EntityType::ITEMWATERPOTION;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMWATERPOTION_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMWATERPOTION_DELAY;
}

ItemWaterPotion::~ItemWaterPotion() {}