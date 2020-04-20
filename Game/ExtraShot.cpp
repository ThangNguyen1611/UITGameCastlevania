#include "ExtraShot.h"

ExtraShot::ExtraShot(float posX, float posY, int type)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::ITEMEXTRASHOT);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::ITEMEXTRASHOT;

	this->posX = posX;
	this->posY = posY;
	typeExtraShot = type;
	if (typeExtraShot == 2)
	{
		sprite->SelectFrame(EXTRASHOT_ANI_DOUBLE);
	}
	else
		if (typeExtraShot == 3)
		{
			sprite->SelectFrame(EXTRASHOT_ANI_TRIPLE);
		}

	vY = EXTRASHOT_GRAVITY;
	timeDisplayed = 0;
	timeDisplayMax = EXTRASHOT_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = EXTRASHOT_TIMEDELAYMAX;
}

ExtraShot::~ExtraShot() {}