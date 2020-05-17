#include "MorningStar.h"

MorningStar::MorningStar()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_MS));
	tag = EntityType::MORNINGSTAR;
	level = 1;
	isDidDamage = false;
}

MorningStar::~MorningStar(){}

void MorningStar::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	Weapon::Update(dt);

	if (animationSet->at(level - 1)->GetCurrentFrame() == 3)
	{
		isDone = true;
	}
}

void MorningStar::Render()
{
	if (isDone)
		return;

	animationSet->at(level - 1)->Render(direction, posX, posY);

	RenderBoundingBox();
}

void MorningStar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//Numbers below is the result of testing
	if (direction == 1)
	{
		left = posX + 50;
		if (level == 1 || level == 2)
		{
			right = posX + 130;
		}
		else if (level == 3)
		{
			right = posX + 160;
		}
	}
	else 
		if (direction == -1)
		{
			right = posX + 92;
			if (level == 1 || level == 2)
			{
				left = posX + 15;
			}
			else if (level == 3)
			{
				left = posX - 15;
			}
		}

	top = posY;
	bottom = posY + 68 - 40;
}

void MorningStar::Attack(float posX, int direction)
{
	isDidDamage = false;
	Weapon::Attack(posX, direction);
	animationSet->at(level - 1)->ResetCurrentFrame();
	animationSet->at(level - 1)->StartAnimation();
}

void MorningStar::ArticulatedPlayerPos(bool isSitting)
{
	posX += 25 * direction;

	if (isSitting)
		posY += 12;
}

bool MorningStar::IsCollidingObject(Entity* Obj)
{
	if (animationSet->at(level - 1)->GetCurrentFrame() == 2 && !isDidDamage)
	{
		if(Weapon::IsCollidingObject(Obj))	//Important: Neu khong xet co the xay ra truong hop 'khong va cham - va khong vao if nay nua')
			isDidDamage = true;
		return Weapon::IsCollidingObject(Obj);
	}

	return false;
}

void MorningStar::UpLevel()
{
	if (level == 3)
		return;

	level++;
	isDone = true;	//ngan khi vua up level thi update va render them lan nua
}