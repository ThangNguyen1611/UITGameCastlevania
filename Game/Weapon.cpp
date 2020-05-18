#include "Weapon.h"

Weapon::Weapon() 
{
	isDone = true;
	isReceivedPos = true;
	damage = 1;
}

Weapon::~Weapon(){}

void Weapon::Attack(float posX, int direction)
{
	//su dung bien isDone nhu khi lam projectiles
	//isDone khi chua danh la true, duoc danh la false
	isDone = false;
	this->direction = direction;
	timeDelayed = 0;
}

void Weapon::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	Entity::Update(dt);
}

void Weapon::Render() 
{
	if (isDone)
		return;
	animationSet->at(0)->Render(direction, posX, posY);
	RenderBoundingBox();
}

bool Weapon::IsCollidingObject(Entity* Obj)
{
	if (Obj->GetHealth() <= 0 || Obj->IsDeadYet() || isDone)
		return false;

	return Entity::IsCollidingObject(Obj);
}

bool Weapon::CheckIsOutCamera(float posX)
{
	if (vX > 0)	//Walking Right
	{
		if (this->posX - posX >= (SCREEN_WIDTH * 0.75))
			return true;
	}
	else if (vX < 0)
	{
		if (posX - this->posX >= (SCREEN_WIDTH * 0.75))
			return true;
	}
	return false;
}