#include "BigHeart.h"

BigHeart::BigHeart(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::BIGHEART);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::BIGHEART;

	this->posX = posX;
	this->posY = posY;
	
	vY = BIGHEART_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = BIGHEART_TIMEDISPLAYMAX; 
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = BIGHEART_TIMEDELAYMAX;
}

BigHeart::~BigHeart(){}