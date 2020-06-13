#pragma once
#include "Weapon.h"
#include "Timer.h"
#include <math.h>

#define PKB_SPEED_X			0.2f	
#define PKB_SPEED_Y			0.02f	
#define PKB_MAX_HEIGHT		50		
#define PKB_DAMAGE			1
#define PKB_MANA_COST		33

#define PKB_BBOX_WIDTH		22
#define PKB_BBOX_HEIGHT		22

#define PKB_DELAY			260		//2 times simon's ani attack
#define PKB_OPEN_DURATION	2000

class Pokeball : public Weapon
{
	float tempY;
	int directionY;
	bool isOpened;
	Timer* openTimer = new Timer(PKB_OPEN_DURATION);
public:
	Pokeball();
	~Pokeball();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, int direction);
};
