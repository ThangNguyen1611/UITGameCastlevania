#include "Effect.h"

Effect::Effect()
{
	isDone = false;
}

Effect::~Effect(){}

void Effect::Update(DWORD dt)
{
	
}

void Effect::Render()
{
	if(!isDone)
		animationSet->at(0)->Render(-1, posX, posY);
}