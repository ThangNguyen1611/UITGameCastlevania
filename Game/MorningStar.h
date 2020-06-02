#pragma once
#include "Weapon.h"

#define MS_INIT_LEVEL				1
#define MS_MAX_LEVEL				3
#define MS_INIT_DAMAGE				1
#define MS_ARTICULATOR_POS_X		25
#define MS_ARTICULATOR_POS_Y		12

#define MS_ENDFRAME					3

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

	void Attack(float posX, int direction);
	void ArticulatedPlayerPos(bool isSitting = false);

	bool IsCollidingObject(Entity* Obj);

	void UpLevel();
	int GetLevel() { return level; }

	void SetDidDamage(bool b) { isDidDamage = b; }
	bool GetDidDamage() { return isDidDamage; }
};

