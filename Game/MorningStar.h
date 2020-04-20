#pragma once
#include "Weapon.h"

#define MORNINGSTAR_ATTACKING_DELAY			130 //equal to PLAYER_ATTACKING_DELAY

#define MORNINGSTAR_LV1_ANI_BEGIN			0
#define MORNINGSTAR_LV1_ANI_END				3

#define MORNINGSTAR_LV2_ANI_BEGIN			4
#define MORNINGSTAR_LV2_ANI_END				7

#define MORNINGSTAR_LV3_ANI_BEGIN			8
#define MORNINGSTAR_LV3_ANI_END				11

class MorningStar : public Weapon
{
	int level;
public:
	MorningStar();
	~MorningStar();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);

	void Attack(float posX, float posY, int direction);
	void ArticulatedPlayerPos(bool isSitting = false);

	bool IsCollidingObject(Entity* Obj);

	void UpLevel();
	int GetLevel() { return level; }
};

