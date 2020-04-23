#include "Candle.h"

Candle::Candle(float posX, float posY, int id)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_CANDLE));
	tag = EntityType::CANDLE;

	this->posX = posX;
	this->posY = posY;
	health = 1;
	isDead = false;
	idCandle = id;
}

Candle::~Candle() {}

void Candle::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		isDead = true;
		return;
	}
}

void Candle::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(-direction, posX, posY);

	RenderBoundingBox();
}

void Candle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + CANDLE_BBOX_WIDTH;
		b = posY + CANDLE_BBOX_HEIGHT;
	}
}