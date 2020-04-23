#include "Torch.h"

Torch::Torch(float posX, float posY, int id)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_TORCH));
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
}

void Torch::Render()
{
	if (isDead)
		return;

	animationSet->at(0)->Render(-direction, posX, posY);
	
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