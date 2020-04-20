#include "Hit.h"

Hit::Hit(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::HITEFFECT);
	this->sprite = new Sprite(texture, MaxFrameRate);
	this->posX = posX;
	this->posY = posY;
	isDone = false;
}

Hit::~Hit(){}

void Hit::Update(DWORD dt)
{
	if (isDone)	//Khong bo vao Effect::Update do khong return duoc Update o day
	{
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (currentFrame < HIT_ANI_BEGIN) {
		sprite->SelectFrame(HIT_ANI_BEGIN);
		sprite->SetCurrentTotalTime(dt);
	}
	else {
		sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
		if (sprite->GetCurrentTotalTime() >= HIT_TIME_OF_PER_EFFECT) {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - HIT_TIME_OF_PER_EFFECT);
			sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
		}

		if (sprite->GetCurrentFrame() > HIT_ANI_END) {
			isDone = true;
		}
	}
}
