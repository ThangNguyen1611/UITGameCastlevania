#include "Bone.h"

Bone::Bone()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_BONE));
	tag = EntityType::BONE;
	timeDelayed = 0;
	timeDelayMax = BONE_DELAY;
	isDidDamage = false;
	damage = BONE_DAMAGE;
}

Bone::~Bone() {}

void Bone::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	timeDelayed += dt;
	if (timeDelayed <= timeDelayMax)
	{
		tempY = posY;
		isReceivedPos = false;
		return;
	}

	if (tempY - posY >= BONE_MAX_HEIGHT)
		directionY = 1;

	if (posY > BOTTOM_SCREEN) 
		isDone = true;

	vY += BONE_SPEED_Y * directionY;		// += bring the parabol-shape fly

	Weapon::Update(dt);
	posX += dx;
	posY += dy;

}

void Bone::Attack(float posX, int direction)
{
	isDidDamage = false;
	Weapon::Attack(posX, direction);
	this->posY -= WEAPON_ARTICULATED_POS_Y;	
	vX = BONE_SPEED_X * this->direction;
	directionY = -1;
	vY = 0;
}

void Bone::Render()
{
	if (timeDelayed <= timeDelayMax)
		return;
	if (isDone)
		return;

	animationSet->at(0)->Render(direction, posX, posY);

	RenderBoundingBox();

}

void Bone::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = posX;
	top = posY;
	right = posX + BONE_BBOX_WIDTH;
	bottom = posY + BONE_BBOX_HEIGHT;
}

bool Bone::IsCollidingObject(Entity* Obj)
{
	if (!isDidDamage)
	{
		if (Weapon::IsCollidingObject(Obj))	
			isDidDamage = true;
		return Weapon::IsCollidingObject(Obj);
	}

	return false;
}

