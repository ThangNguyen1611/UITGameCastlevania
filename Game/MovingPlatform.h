#pragma once
#include "Entity.h"

#define PLAT_BBOX_WIDTH			64
#define PLAT_BBOX_HEIGHT		16

#define PLAT_MOVING_SPEED		0.1f	//50% player's speed		

class MovingPlatform : public Entity
{
public:
	MovingPlatform(float posX, float posY);
	~MovingPlatform();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
