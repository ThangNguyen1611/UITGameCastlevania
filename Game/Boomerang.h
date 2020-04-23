#pragma once
#include "Weapon.h"
#include <math.h>

#define BOOMERANG_SPEED_X		0.25f

#define BOOMERANG_BBOX_WIDTH	28
#define BOOMERANG_BBOX_HEIGHT	28

#define BOOMERANG_MAX_DISTANCE	300

#define MAX_BOOMERANG_DELAY		260		//2 times simon's ani attack

class Boomerang : public Weapon
{
	float ownerPosX;
	int ownerDirection;
	float timeDelayed, timeDelayMax;
	LPGAMEENTITY owner;
public:
	Boomerang(LPGAMEENTITY owner);
	~Boomerang();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, float posY, int direction);

	void ResetDelay() { timeDelayed = 0; }
};
