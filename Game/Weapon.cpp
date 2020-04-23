#include "Weapon.h"

Weapon::Weapon() 
{
	isDone = true;
}

Weapon::~Weapon(){}

void Weapon::Attack(float posX, float posY, int direction)
{
	//su dung bien isDone nhu khi lam projectiles
	//isDone khi chua danh la true, duoc danh la false
	isDone = false;
	this->posX = posX;
	this->posY = posY;
	this->direction = direction;
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
