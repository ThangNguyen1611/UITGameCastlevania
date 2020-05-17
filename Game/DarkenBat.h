#pragma once
#include "Entity.h"

#define DARKBAT_FLYING_SPEED_X			0.15f
#define DARKBAT_FLYING_SPEED_PHASE2		3.0f
#define DARKBAT_FLYING_SPEED_Y			0.02f
#define DARKBAT_AMPLITUDE_HORIZONTAL	40	
#define DARKBAT_MAX_DISTANCE_PHASE1		150

#define DARKBAT_BBOX_WIDTH				32
#define DARKBAT_BBOX_HEIGHT				32

#define DARKBAT_STATE_INACTIVE			0
#define DARKBAT_STATE_FLYING			1
#define DARKBAT_STATE_DIE				-1

class DarkenBat : public Entity
{
	float tempY;
	int directionY;
	LPGAMEENTITY target;
	float firstPosX;
	bool isDonePhase1;	//Phase 1: A curve-shape movement || Phase 2: Fly toward target
public:
	DarkenBat(float posX, float posY, int directionX, LPGAMEENTITY target);
	~DarkenBat();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
};

