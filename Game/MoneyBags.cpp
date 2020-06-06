#include "MoneyBags.h"

MoneyBags::MoneyBags(float posX, float posY, EntityType typeBag)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_MONEYBAGS));
	tag = typeBag;

	this->posX = posX;
	this->posY = posY;

	displayTimer = new Timer(BAGS_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = BAGS_DELAY;
}

MoneyBags::~MoneyBags(){}

void MoneyBags::Render()
{
	if (isDone || delayStart <= delayLimit)
		return;
	//khong dung lai Item::Render do muon return som tai day 
	switch (tag)
	{
	case MONEYBAGRED:
		animationSet->at(0)->Render(-direction, posX, posY);
		break;
	case MONEYBAGWHITE:
		animationSet->at(1)->Render(-direction, posX, posY);
		break;
	case MONEYBAGBLUE:
		animationSet->at(2)->Render(-direction, posX, posY);
		break;
	default:
		break;
	}

	RenderBoundingBox();
}
