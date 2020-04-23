#include "ItemDagger.h"

ItemDagger::ItemDagger(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMDAGGER));
	tag = EntityType::ITEMDAGGER;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMDAGGER_GRAVITY;
	displayTimer = new Timer(ITEMDAGGER_TIMEDISPLAYMAX);
	displayTimer->Start();
}

ItemDagger::~ItemDagger() {}