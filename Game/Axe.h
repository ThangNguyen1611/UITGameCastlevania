#pragma once
#include "Weapon.h"
#include <math.h>

#define AXE_SPEED_X					0.2f	//15
#define AXE_SPEED_Y					0.02f	//2
#define AXE_MAX_DISTANCE_HEIGHT		50		//150

#define AXE_BBOX_WIDTH		30
#define AXE_BBOX_HEIGHT		28

#define MAX_AXE_DELAY		260		//2 times simon's ani attack

class Axe : public Weapon
{
	float tempY;
	int directionY;
public:
	Axe();
	~Axe();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, int direction);
};
