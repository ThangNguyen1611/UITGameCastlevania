#include "Score.h"

Score::Score(float posX, float posY, EntityType scoreType)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ADDSCORE));
	this->posX = posX;
	this->posY = posY;
	isDone = false;
	SetType(scoreType);
}

Score::~Score() {}

void Score::Update(DWORD dt)
{
	if (isDone)	//Khong bo vao Effect::Update do khong return duoc Update o day
	{
		return;
	}
	if(animationSet->at(type)->GetCurrentFrame() == 1)
	{
		isDone = true;
		animationSet->at(type)->ResetCurrentFrame();
	}
}

void Score::Render()
{
	if (!isDone)
		animationSet->at(type)->Render(-1, posX, posY);
}

void Score::SetType(EntityType scoreType)
{
	switch (scoreType)
	{
	case MONEYBAGRED:
		type = SCORE_100_ANI;
		break;
	case MONEYBAGWHITE:
		type = SCORE_400_ANI;
		break;
	case MONEYBAGBLUE:
		type = SCORE_700_ANI;
		break;
	default:
		type = SCORE_1000_ANI;
		break;
	}
}

