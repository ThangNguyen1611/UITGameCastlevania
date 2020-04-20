#include "Score.h"

Score::Score(float posX, float posY, EntityType scoreType)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::ADDSCOREEFFECT);
	this->sprite = new Sprite(texture, MaxFrameRate);
	this->posX = posX;
	this->posY = posY;
	isDone = false;
	this->scoreType = scoreType;
}

Score::~Score() {}

void Score::Update(DWORD dt)
{
	if (isDone)	//Khong bo vao Effect::Update do khong return duoc Update o day
	{
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (scoreType == EntityType::MONEYBAGRED)
	{
		if (currentFrame < SCORE_100_ANI_BEGIN) {
			sprite->SelectFrame(SCORE_100_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= SCORE_TIME_OF_PER_EFFECT) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - SCORE_TIME_OF_PER_EFFECT);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > SCORE_100_ANI_END) {
				isDone = true;
			}
		}
	}
	else if (scoreType == EntityType::MONEYBAGWHITE)
	{
		if (currentFrame < SCORE_400_ANI_BEGIN) {
			sprite->SelectFrame(SCORE_400_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= SCORE_TIME_OF_PER_EFFECT) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - SCORE_TIME_OF_PER_EFFECT);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > SCORE_400_ANI_END) {
				isDone = true;
			}
		}
	}
	else if (scoreType == EntityType::MONEYBAGBLUE)
	{
		if (currentFrame < SCORE_700_ANI_BEGIN) {
			sprite->SelectFrame(SCORE_700_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= SCORE_TIME_OF_PER_EFFECT) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - SCORE_TIME_OF_PER_EFFECT);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > SCORE_700_ANI_END) {
				isDone = true;
			}
		}
	}
	else
	{
		if (currentFrame < SCORE_1000_ANI_BEGIN) {
			sprite->SelectFrame(SCORE_1000_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= SCORE_TIME_OF_PER_EFFECT) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - SCORE_TIME_OF_PER_EFFECT);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > SCORE_1000_ANI_END) {
				isDone = true;
			}
		}
	}
}

