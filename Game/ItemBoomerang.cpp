#include "ItemBoomerang.h"

ItemBoomerang::ItemBoomerang(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::ITEMBOOMERANG);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::ITEMBOOMERANG;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMBOOMERANG_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = ITEMBOOMERANG_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = ITEMBOOMERANG_TIMEDELAYMAX;
}

ItemBoomerang::~ItemBoomerang() {}