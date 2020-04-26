#include "ExtraShot.h"

ExtraShot::ExtraShot(float posX, float posY, int type)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMEXTRASHOT));
	tag = EntityType::ITEMEXTRASHOT;

	this->posX = posX;
	this->posY = posY;
	typeExtraShot = type - 2;
	vY = EXTRASHOT_GRAVITY;
	displayTimer = new Timer(EXTRASHOT_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = EXTRASHOT_TIMEDELAYMAX;
}

ExtraShot::~ExtraShot() {}