#include "Brick.h"

Brick::Brick(float posX, float posY, int brickType)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::BRICK);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::BRICK;

	this->posX = posX;
	this->posY = posY;
	this->brickType = brickType;
}

Brick::~Brick() {}

void Brick::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (brickType == 1)
		sprite->SelectFrame(BRICK_TYPE1);
	else if(brickType == 2)
		sprite->SelectFrame(BRICK_TYPE2);
	else if(brickType == 3)
		sprite->SelectFrame(BRICK_TYPE3);
	else if (brickType == 4)
		sprite->SelectFrame(BRICK_TYPE4);
}

void Brick::Render()
{
	sprite->Draw(posX, posY);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX;
	t = posY;
	r = posX + BRICK_BBOX_WIDTH;
	b = posY + BRICK_BBOX_HEIGHT;
}
