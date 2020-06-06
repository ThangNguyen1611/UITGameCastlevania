#include "ItemDagger.h"

ItemDagger::ItemDagger(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMDAGGER));
	tag = EntityType::ITEMDAGGER;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMDAGGER_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMDAGGER_DELAY;
}

ItemDagger::~ItemDagger() {}