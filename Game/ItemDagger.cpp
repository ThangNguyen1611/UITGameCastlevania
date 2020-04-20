#include "ItemDagger.h"

ItemDagger::ItemDagger(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::ITEMDAGGER);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::ITEMDAGGER;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMDAGGER_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = ITEMDAGGER_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = ITEMDAGGER_TIMEDELAYMAX;
}

ItemDagger::~ItemDagger() {}