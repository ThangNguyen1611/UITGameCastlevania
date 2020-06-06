#include "ExtraShot.h"

ExtraShot::ExtraShot(float posX, float posY, int type)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMEXTRASHOT));
	tag = EntityType::ITEMEXTRASHOT;

	this->posX = posX;
	this->posY = posY;
	typeExtraShot = type;

	displayTimer = new Timer(EXTRASHOT_DISPLAY_DURATION);
	displayTimer->Start();
	delayLimit = EXTRASHOT_DELAY;
}

ExtraShot::~ExtraShot() {}

void ExtraShot::Render()
{
	if (isDone || delayStart <= delayLimit)
		return;

	animationSet->at(typeExtraShot - 2)->Render(-direction, posX, posY);

	RenderBoundingBox();
}