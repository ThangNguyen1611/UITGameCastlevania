#include "ItemBoomerang.h"

ItemBoomerang::ItemBoomerang(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMBMR));
	tag = EntityType::ITEMBOOMERANG;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMBOOMERANG_GRAVITY;
	displayTimer = new Timer(ITEMBOOMERANG_TIMEDISPLAYMAX);
	displayTimer->Start();
}

ItemBoomerang::~ItemBoomerang() {}