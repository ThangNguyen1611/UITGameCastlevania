#pragma once
#include "Entity.h"

#define GHOST_FLYING_SPEED			1.25f

#define GHOST_BBOX_WIDTH			32
#define GHOST_BBOX_HEIGHT			32

#define GHOST_STATE_FLYING			1
#define GHOST_STATE_DIE				-1
class Ghost : public Entity
{
	LPGAMEENTITY target;
public:
	Ghost(float posX, float posY, LPGAMEENTITY owner);
	~Ghost();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

};

