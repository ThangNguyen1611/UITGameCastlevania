#include "DarkenBat.h"
#include <math.h>
#define PI 3.141562535898

DarkenBat::DarkenBat(float posX, float posY, int directionX, LPGAMEENTITY target)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::DARKENBAT);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::DARKENBAT;

	this->posX = posX;
	this->posY = posY;
	this->tempY = posY;
	this->direction = directionX;

	this->SetState(DARKBAT_STATE_INACTIVE);

	health = 1;
	isDead = false;
	targetDetected = false;
	this->target = target;
}

DarkenBat::~DarkenBat(){}

void DarkenBat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 0)
	{
		SetState(DARKBAT_STATE_DIE);
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (!isDead)
	{
		if (!targetDetected)
		{
			sprite->SelectFrame(DARKBAT_ANI_INACTIVE);
		}
		else
		{
			if (currentFrame < DARKBAT_ANI_FLYING_BEGIN) {
				sprite->SelectFrame(DARKBAT_ANI_FLYING_BEGIN);
				sprite->SetCurrentTotalTime(dt);
			}
			else {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
				if (sprite->GetCurrentTotalTime() >= DARKBAT_FLAPPING_SPEED) {
					sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - DARKBAT_FLAPPING_SPEED);
					sprite->SelectFrame(sprite->GetCurrentFrame() + 1);
				}

				if (sprite->GetCurrentFrame() > DARKBAT_ANI_FLYING_END) {
					sprite->SelectFrame(DARKBAT_ANI_FLYING_BEGIN);
				}
			}
		}
	}

	if (target != NULL)
	{
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= 200)
		{
			targetDetected = true;
			SetState(DARKBAT_STATE_FLYING);
		}
	}

	if (vX != 0)
	{
		//posY = 60 * sin(0.3 * posX * PI / 180) + tempY;
		//posY = ((-1 * pow(posX, 2)) / 125) + (1057 * posX / 288) - 214;
		posY = ((-23 * pow(posX, 2)) / 2702) + (123 * posX / 32) - 227;
	}

	Entity::Update(dt);
	posX += dx;
	posY += dy;

}

void DarkenBat::Render()
{
	if (isDead)
		return;

	if (direction == 1) {
		sprite->DrawFlipVertical(posX, posY, 255);
	}
	else {
		sprite->Draw(posX, posY, 255);
	}
	RenderBoundingBox();
}


void DarkenBat::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case DARKBAT_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case DARKBAT_STATE_FLYING:
		vX = DARKBAT_FLYING_SPEED_X * direction;
		break;
	case DARKBAT_STATE_INACTIVE:
		vX = 0;
		vY = 0;
		break;
	}
}

void DarkenBat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead) 
	{
		l = posX;
		t = posY;
		r = posX + DARKBAT_BBOX_WIDTH;
		b = posY + DARKBAT_BBOX_HEIGHT;
	}
}