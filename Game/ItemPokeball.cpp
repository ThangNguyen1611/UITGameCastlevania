#include "ItemPokeball.h"

ItemPokeball::ItemPokeball(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMPOKEBALL));
	tag = EntityType::ITEMPOKEBALL;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMPOKEBALL_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMPOKEBALL_DELAY;
}

ItemPokeball::~ItemPokeball() {}