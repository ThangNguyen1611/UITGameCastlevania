#include "Torch.h"

Torch::Torch(float posX, float posY, int id)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::TORCH);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::TORCH;

	this->posX = posX;
	this->posY = posY;
	health = 1;
	isDead = false;
	idTorch = id;
}

Torch::~Torch(){}

void Torch::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0) 
	{
		isDead = true;
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (!isDead) {
		if (currentFrame < TORCH_ANI_BEGIN) {
			sprite->SelectFrame(TORCH_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= TORCH_BURN_SPEED) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - TORCH_BURN_SPEED);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
			}

			if (sprite->GetCurrentFrame() > TORCH_ANI_END) {
				sprite->SelectFrame(TORCH_ANI_BEGIN);
			}
		}
	}
}

void Torch::Render()
{
	if (isDead)
		return;

	sprite->Draw(posX, posY);
	
	RenderBoundingBox();
}

void Torch::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + TORCH_BBOX_WIDTH;
		b = posY + TORCH_BBOX_HEIGHT;
	}
}