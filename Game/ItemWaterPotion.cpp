#include "ItemWaterPotion.h"

ItemWaterPotion::ItemWaterPotion(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMWATERPOTION));
	tag = EntityType::ITEMWATERPOTION;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMWATERPOTION_GRAVITY;
	displayTimer = new Timer(ITEMWATERPOTION_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = ITEMWATERPOTION_TIMEDELAYMAX;
}

ItemWaterPotion::~ItemWaterPotion() {}