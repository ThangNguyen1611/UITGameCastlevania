#include "Stairs.h"

Stairs::Stairs(float posX, float posY, int stairDirection, int stairDirectionY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::STAIRS);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::STAIRS;

	this->posX = posX;
	this->posY = posY;
	this->direction = stairDirection;
	this->directionY = stairDirectionY;
}

Stairs::~Stairs(){}

void Stairs::Render()
{
	if (direction == 1) 
	{
		sprite->SelectFrame(STAIRS_RIGHTWAY);
	}
	else
	{
		sprite->SelectFrame(STAIRS_LEFTWAY);
	}
	sprite->Draw(posX, posY);
	RenderBoundingBox();
}

void Stairs::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX;
	t = posY;
	r = posX + STAIRS_BBOX_WIDTH;
	b = posY + STAIRS_BBOX_HEIGHT;
}
