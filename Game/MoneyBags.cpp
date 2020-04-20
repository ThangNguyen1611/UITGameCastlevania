#include "MoneyBags.h"

MoneyBags::MoneyBags(float posX, float posY, EntityType typeBag)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::MONEYBAGS);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = typeBag;

	this->posX = posX;
	this->posY = posY;

	vY = BAGS_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = BAGS_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = BAGS_TIMEDELAYMAX;
}

MoneyBags::~MoneyBags(){}

void MoneyBags::Render()
{
	if (timeDelayDisplayed < timeDelayDisplayMax)
		return;
	if (isDone)
		return;
	//khong dung lai Item::Render do muon return som tai day 
	switch (tag)
	{
	case MONEYBAGRED:
		sprite->SelectFrame(BAG_RED);
		break;
	case MONEYBAGWHITE:
		sprite->SelectFrame(BAG_WHITE);
		break;
	case MONEYBAGBLUE:
		sprite->SelectFrame(BAG_BLUE);
		break;
	default:
		break;
	}

	sprite->Draw(posX, posY);

	RenderBoundingBox();
}
