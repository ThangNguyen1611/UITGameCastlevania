#pragma once
#include "Weapon.h"
#include "Timer.h"
#include <math.h>

#define WATPOT_SPEED_X					0.2f
#define WATPOT_SPEED_Y					0.02f
#define WATPOT_MAX_HEIGHT				25
#define WATPOT_DAMAGE					1

#define WATPOT_BBOX_WIDTH				32
#define WATPOT_BBOX_HEIGHT				26

#define WATPOT_DELAY					260		//2 times simon's ani attack

#define WATPOT_STATE_POT				0
#define WATPOT_STATE_BURN				1

#define WATPOT_BURN_DURATION			1200

class WaterPotion : public Weapon
{
	float tempY;
	int directionY;
	Timer* burnDuration = new Timer(WATPOT_BURN_DURATION);
public:
	WaterPotion();
	~WaterPotion();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();
	void SetState(int state);

	void Attack(float posX, int direction);
	bool IsCollidingObject(Entity* Obj);
};
