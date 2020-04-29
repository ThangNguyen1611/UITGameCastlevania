#pragma once
#include "Weapon.h"
#include <math.h>

#define BOOMERANG_SPEED_X		0.25f

#define BOOMERANG_BBOX_WIDTH	28
#define BOOMERANG_BBOX_HEIGHT	28

#define BOOMERANG_MAX_DISTANCE	450

#define MAX_BOOMERANG_DELAY		260		//2 times simon's ani attack

class Boomerang : public Weapon
{
	float ownerPosX;
	int ownerDirection;
	LPGAMEENTITY owner;
	bool isDidDamageTurn1, isDidDamageTurn2;
public:
	Boomerang(LPGAMEENTITY owner);
	~Boomerang();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, int direction);

	bool GetIsDidDamageTurn1() { return isDidDamageTurn1; }
	void SetIsDidDamageTurn1(bool isDid) { isDidDamageTurn1 = isDid; }
	bool GetIsDidDamageTurn2() { return isDidDamageTurn2; }
	void SetIsDidDamageTurn2(bool isDid) { isDidDamageTurn2 = isDid; }
	int GetOwnerDirection() { return ownerDirection; }
};
