#pragma once
#include "Entity.h"

#define ZOMBIE_WALKING_SPEED		0.15f
#define ZOMBIE_GRAVITY				0.002f
#define ZOMBIE_MAX_DISTANCE			1200.0f

#define ZOMBIE_BBOX_WIDTH			32
#define ZOMBIE_BBOX_HEIGHT			64

#define ZOMBIE_STATE_WALKING		100
#define ZOMBIE_STATE_DIE			200

#define ZOMBIE_ANI_WALKING_BEGIN	0
#define ZOMBIE_ANI_WALKING_END		1

#define ZOMBIE_DRESSDANCE_SPEED		300.0f

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

