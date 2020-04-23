#include "Score.h"

Score::Score(float posX, float posY, EntityType scoreType)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ADDSCORE));
	this->posX = posX;
	this->posY = posY;
	isDone = false;
	this->scoreType = scoreType;

	/*if (scoreType == EntityType::MONEYBAGRED)
	{
		animationSet->at(SCORE_100_ANI)->StartAnimation();
	}
	else if (scoreType == EntityType::MONEYBAGWHITE)
	{
		animationSet->at(SCORE_400_ANI)->StartAnimation();
	}
	else if (scoreType == EntityType::MONEYBAGBLUE)
	{
		animationSet->at(SCORE_700_ANI)->StartAnimation();
	}*/
	/*else
		animationSet->at(SCORE_1000_ANI)->StartAnimation();*/
}

Score::~Score() {}

void Score::Update(DWORD dt)
{
	if (isDone)	//Khong bo vao Effect::Update do khong return duoc Update o day
	{
		return;
	}
	/*if(scoreType == EntityType::MONEYBAGRED && animationSet->at(SCORE_100_ANI)->IsRenderOver(SCORE_DISPLAY))
	{
		isDone = true;
	}
	else if (scoreType == EntityType::MONEYBAGWHITE && animationSet->at(SCORE_400_ANI)->IsRenderOver(SCORE_DISPLAY))
	{
		isDone = true;
	}
	else if (scoreType == EntityType::MONEYBAGBLUE && animationSet->at(SCORE_700_ANI)->IsRenderOver(SCORE_DISPLAY))
	{
		isDone = true;
	}*/
	/*else if (animationSet->at(SCORE_1000_ANI)->IsRenderOver(SCORE_DISPLAY))
	{
		isDone = true;
	}*/
}

void Score::Render()
{
	if (!isDone)
	{
		/*switch (scoreType)
		{
		case MONEYBAGRED:
			animationSet->at(SCORE_100_ANI)->Render(-1, posX, posY);
			break;
		case MONEYBAGWHITE:
			animationSet->at(SCORE_400_ANI)->Render(-1, posX, posY);
			break;
		case MONEYBAGBLUE:
			animationSet->at(SCORE_700_ANI)->Render(-1, posX, posY);
			break;
		default:
			animationSet->at(SCORE_1000_ANI)->Render(-1, posX, posY);
			break;
		}*/
	}
}

