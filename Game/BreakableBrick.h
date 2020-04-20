#pragma once
#include "Entity.h"

#define BBRICK_BBOX_WIDTH  32
#define BBRICK_BBOX_HEIGHT 32

#define BBRICK_TYPE1		0
#define BBRICK_TYPE2		1
#define BBRICK_TYPE3		2
#define BBRICK_TYPE4		3

class BreakableBrick : public Entity
{
	int brickType;
public:
	BreakableBrick(float posX, float posY, int type = 1);
	~BreakableBrick();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = 0);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);

};

