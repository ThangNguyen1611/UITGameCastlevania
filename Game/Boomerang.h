#pragma once
#include "Weapon.h"
#include <math.h>

#define BOOMERANG_SPEED_X		0.25f

#define BOOMERANG_MAX_DISTANCE	300

#define MAX_BOOMERANG_DELAY		220		//2 times simon's ani attack

#define BOOMERANG_ANI_BEGIN		0
#define BOOMERANG_ANI_END		2
#define BOOMERANG_SWITCH_SPEED	120

class Boomerang : public Weapon
{
	float ownerPosX;
	int ownerDirection;
	float timeDelayed, timeDelayMax;
	LPGAMEENTITY owner;
public:
	Boomerang(LPGAMEENTITY owner);
	~Boomerang();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, float posY, int direction);

	void ResetDelay() { timeDelayed = 0; }
};
