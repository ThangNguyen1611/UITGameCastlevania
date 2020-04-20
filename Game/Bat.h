#pragma once
#include "Entity.h"

#define BAT_FLYING_SPEED_X			0.15f
#define BAT_FLYING_SPEED_Y			0.1f
#define BAT_AMPLITUDE_HORIZONTAL	30.0f	

#define BAT_BBOX_WIDTH				32
#define BAT_BBOX_HEIGHT				32

#define BAT_STATE_FLYING			100
#define BAT_STATE_DIE				200

#define BAT_ANI_FLYING_BEGIN		1
#define BAT_ANI_FLYING_END			3

#define BAT_FLAPPING_SPEED			130 

class Bat : public Entity
{
	int directionY;
	float tempY;
public:
	Bat(float posX, float posY, int direction = 1);
	~Bat();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

};

