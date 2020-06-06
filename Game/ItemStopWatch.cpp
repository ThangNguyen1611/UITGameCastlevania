#include "ItemStopWatch.h"

ItemStopWatch::ItemStopWatch(float posX, float posY)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMSTOPWATCH));
	tag = EntityType::ITEMSTOPWATCH;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(ITEMSTOPWATCH_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = ITEMSTOPWATCH_DELAY;
}

ItemStopWatch::~ItemStopWatch() {}