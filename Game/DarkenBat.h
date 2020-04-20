#pragma once
#include "Entity.h"

#define DARKBAT_FLYING_SPEED_X			0.15f
#define DARKBAT_FLYING_SPEED_Y			0.1f
#define DARKBAT_AMPLITUDE_HORIZONTAL	30.0f	

#define DARKBAT_BBOX_WIDTH				32
#define DARKBAT_BBOX_HEIGHT				32

#define DARKBAT_STATE_INACTIVE			0
#define DARKBAT_STATE_FLYING			100
#define DARKBAT_STATE_DIE				200

#define DARKBAT_ANI_INACTIVE			0
#define DARKBAT_ANI_FLYING_BEGIN		1
#define DARKBAT_ANI_FLYING_END			3

#define DARKBAT_FLAPPING_SPEED			130 

class DarkenBat : public Entity
{
	float tempY;
	bool targetDetected;
	LPGAMEENTITY target;
public:
	DarkenBat(float posX, float posY, int directionX, LPGAMEENTITY target);
	~DarkenBat();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
};

