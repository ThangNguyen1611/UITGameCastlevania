#include "StopWatch.h"

StopWatch::StopWatch()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMSTOPWATCH));
	tag = EntityType::STOPWATCH;
}

StopWatch::~StopWatch() {}

void StopWatch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + 1;
	bottom = posY + 1;
}