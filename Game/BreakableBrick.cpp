#include "BreakableBrick.h"


BreakableBrick::BreakableBrick(float posX, float posY, int type)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::BREAKABLEBRICK);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::BREAKABLEBRICK;

	this->posX = posX;
	this->posY = posY;
	health = 1;
	isDead = false;
	brickType = type;
}

BreakableBrick::~BreakableBrick() {}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		isDead = true;
		return;
	}

	if (brickType == 1)
		sprite->SelectFrame(BBRICK_TYPE1);
	else if (brickType == 2)
		sprite->SelectFrame(BBRICK_TYPE2);
	else if (brickType == 3)
		sprite->SelectFrame(BBRICK_TYPE3);
	else if (brickType == 4)
		sprite->SelectFrame(BBRICK_TYPE4);
}

void BreakableBrick::Render()
{
	if (isDead)
		return;

	sprite->Draw(posX, posY);

	RenderBoundingBox();
}

void BreakableBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + BBRICK_BBOX_WIDTH;
		b = posY + BBRICK_BBOX_HEIGHT;
	}
}
