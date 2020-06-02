#include "UpgradeMorningStar.h"

UpgradeMorningStar::UpgradeMorningStar(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_UPGRADEMS));
	tag = EntityType::UPGRADEMORNINGSTAR;

	this->posX = posX;
	this->posY = posY;

	vY = UPGRADEMS_GRAVITY;
	displayTimer = new Timer(UPGRADEMS_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = UPGRADEMS_DELAY;
}

UpgradeMorningStar::~UpgradeMorningStar() {}
