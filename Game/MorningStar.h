#pragma once
#include "Weapon.h"

class MorningStar : public Weapon
{
	int level;
	bool isDidDamage;
public:
	MorningStar();
	~MorningStar();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, float posY, int direction);
	void ArticulatedPlayerPos(bool isSitting = false);

	bool IsCollidingObject(Entity* Obj);

	void UpLevel();
	int GetLevel() { return level; }
};

