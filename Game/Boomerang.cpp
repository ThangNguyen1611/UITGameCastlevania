#include "Boomerang.h"

Boomerang::Boomerang(LPGAMEENTITY owner)
{
	texture = Texture2dManager::GetInstance()->GetTexture(EntityType::BOOMERANG);
	sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::BOOMERANG;
	ownerPosX = 0;
	timeDelayed = 0;
	timeDelayMax = MAX_BOOMERANG_DELAY;

	this->owner = owner;
}

Boomerang::~Boomerang() {}

void Boomerang::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	
	Weapon::Update(dt);
	posX += dx;

	int currentFrame = sprite->GetCurrentFrame();
	if (!isDone) {
		if (currentFrame < BOOMERANG_ANI_BEGIN)
		{
			sprite->SelectFrame(BOOMERANG_ANI_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= BOOMERANG_SWITCH_SPEED)
			{
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - BOOMERANG_SWITCH_SPEED);
				sprite->SelectFrame(currentFrame + 1);
			}

			if (sprite->GetCurrentFrame() > BOOMERANG_ANI_END) {
				sprite->SelectFrame(BOOMERANG_ANI_BEGIN);
			}
		}
	}

	if (ownerDirection == direction)	//state nem' di
	{
		if (abs(ownerPosX - this->posX) >= BOOMERANG_MAX_DISTANCE)
		{
			direction *= -1;
			vX *= -1;
		}
	}	
	else	//state quay ve
	{
		if (IsCollidingObject(owner) || abs(ownerPosX - this->posX) >= 1.5*BOOMERANG_MAX_DISTANCE)	//cham simon
		{
			isDone = true;
		}
	}
}

void Boomerang::Attack(float posX, float posY, int direction)
{
	Weapon::Attack(posX, posY, direction);
	ownerPosX = posX;
	ownerDirection = direction;
	this->posY -= 8;	//Fit Simon Hand
	vX = BOOMERANG_SPEED_X * this->direction;
}

void Boomerang::Render()
{
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	if (isDone)
		return;
	if (direction == -1) //Right direction
	{
		sprite->DrawFlipVertical(posX, posY);
	}
	else
	{
		sprite->Draw(posX, posY);
	}

	RenderBoundingBox();

}
