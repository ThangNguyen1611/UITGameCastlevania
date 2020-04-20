#include "Dagger.h"

Dagger::Dagger()
{
	texture = Texture2dManager::GetInstance()->GetTexture(EntityType::DAGGER);
	sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::DAGGER;
	ownerPosX = 0;
	timeDelayed = 0;
	timeDelayMax = MAX_DAGGER_DELAY;
}

Dagger::~Dagger(){}

void Dagger::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		return;
	}
	if (CheckIsOutCamera(ownerPosX))
	{
		isDone = true;
		return;
	}
	Weapon::Update(dt);
	posX += dx;
}

void Dagger::Attack(float posX, float posY, int direction)
{
	Weapon::Attack(posX, posY, direction);
	ownerPosX = posX;
	this->posY -= 8;	//Fit Simon Hand
	vX = DAGGER_SPEED_X * this->direction;
}

void Dagger::Render()
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

bool Dagger::CheckIsOutCamera(float posX)
{
	//Dieu nay thuc te hon trong game
	//Trong game la con trong ban kinh camera thi isdone = false
	//Nhung thuc te thi o ngoai dau co cai camera nao ? ma la khoang cach nhat dinh dua vao nguoi nem 
	if (vX > 0)	//Walking Right
	{
		if (this->posX - posX >= (SCREEN_WIDTH / 2))
			return true;
	}
	else if (vX < 0)
	{
		if (posX - this->posX >= (SCREEN_WIDTH / 2))
			return true;
	}
	return false;
}
