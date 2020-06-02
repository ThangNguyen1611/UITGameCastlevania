#pragma once
#include "Entity.h"

#define GHOST_FLYING_SPEED			1.25f
#define GHOST_MAXHEALTH				2
#define GHOST_CLOSED_RANGE			20
#define GHOST_DAMAGE				3

#define GHOST_BBOX_WIDTH			32
#define GHOST_BBOX_HEIGHT			32

#define GHOST_STATE_FLYING			1
#define GHOST_STATE_DIE				-1

#define GHOST_CYCLE_TIME_RANDOM		3000
#define GHOST_INIT_TOTALTIME		2000
class Ghost : public Entity
{
	LPGAMEENTITY target;
	DWORD currentTotalTime;
	int randomPosX, randomPosY;
	int dirY;
public:
	Ghost(float posX, float posY, LPGAMEENTITY owner);
	~Ghost();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void SelfDestroy();
};

