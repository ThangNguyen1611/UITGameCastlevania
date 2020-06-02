#pragma once
#include "Entity.h"

#define BUSH_FADED				75

#define BUSH_BBOX_WIDTH			140
#define BUSH_BBOX_HEIGHT		68

class Bush : public Entity
{
	LPGAMEENTITY player;
	bool isPlayerInside;
public:
	Bush(float posX, float posY, LPGAMEENTITY player);
	~Bush();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = 0);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
};