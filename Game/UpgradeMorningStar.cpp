#include "UpgradeMorningStar.h"

UpgradeMorningStar::UpgradeMorningStar(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::UPGRADEMORNINGSTAR);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::UPGRADEMORNINGSTAR;

	this->posX = posX;
	this->posY = posY;

	vY = UPGRADEMS_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = UPGRADEMS_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = UPGRADEMS_TIMEDELAYMAX;
}

UpgradeMorningStar::~UpgradeMorningStar() {}
