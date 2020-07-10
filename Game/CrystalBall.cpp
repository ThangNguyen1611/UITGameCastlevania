#include "CrystalBall.h"

CrystalBall::CrystalBall(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CRYSTALBALL));
	tag = EntityType::CRYSTALBALL;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(CRYSTALBALL_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = CRYSTALBALL_DELAY;
}

CrystalBall::~CrystalBall() {}