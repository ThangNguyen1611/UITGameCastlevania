#include "ItemStopWatch.h"

ItemStopWatch::ItemStopWatch(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMSTOPWATCH));
	tag = EntityType::ITEMSTOPWATCH;

	this->posX = posX;
	this->posY = posY;

	vY = ITEMSTOPWATCH_GRAVITY;
	displayTimer = new Timer(ITEMSTOPWATCH_TIMEDISPLAYMAX);
	displayTimer->Start();
	delayLimit = ITEMSTOPWATCH_TIMEDELAYMAX;
}

ItemStopWatch::~ItemStopWatch() {}