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
		sprite->Draw(posX, posY);
}