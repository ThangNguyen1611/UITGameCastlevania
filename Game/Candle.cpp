#include "Candle.h"

Candle::Candle(float posX, float posY, int id)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::CANDLE);
	this->sprite = new Sprite(texture, MaxFrameRate);
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

	int currentFrame = sprite->GetCurrentFrame();
	if (!isDead) {
		if (currentFrame < CANDLE_ANI_BEGIN) {
			sprite->SelectFrame(CANDLE_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= CANDLE_BURN_SPEED) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - CANDLE_BURN_SPEED);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > CANDLE_ANI_END) {
				sprite->SelectFrame(CANDLE_ANI_BEGIN);
			}
		}
	}
}

void Candle::Render()
{
	if (isDead)
		return;

	sprite->Draw(posX, posY);

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