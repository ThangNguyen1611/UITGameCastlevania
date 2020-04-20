#pragma once
#include "Entity.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

#define BRICK_TYPE1		0
#define BRICK_TYPE2		1
#define BRICK_TYPE3		2
#define BRICK_TYPE4		3

class Brick : public Entity
{
public:
	int brickType;

	Brick(float posX, float posY, int brickType = 1);
	~Brick();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};