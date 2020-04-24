#include "Effect.h"

Effect::Effect()
{
	isDone = false;
}

Effect::~Effect(){}

void Effect::Render()
{
	if(!isDone)
		animationSet->at(0)->Render(-1, posX, posY);
}