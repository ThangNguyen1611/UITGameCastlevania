#pragma once
#include "Entity.h"

#define ZOMBIE_WALKING_SPEED_X		0.15f
#define ZOMBIE_GRAVITY				0.002f
#define ZOMBIE_WALKING_RANGE		1200.0f
#define ZOMBIE_MAXHEALTH			1

#define ZOMBIE_BBOX_WIDTH			32
#define ZOMBIE_BBOX_HEIGHT			64

#define ZOMBIE_STATE_WALKING		0
#define ZOMBIE_STATE_DIE			-1

class Zombie : public Entity
{
public:
	Zombie(float posX, float posY, int direction = 1);
	~Zombie();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
};

