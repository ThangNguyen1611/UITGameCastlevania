#pragma once
#include "Entity.h"

#define STAIRS_BBOX_WIDTH		32
#define STAIRS_BBOX_HEIGHT		32

#define STAIRS_RIGHTWAY			0
#define STAIRS_LEFTWAY			1

class Stairs : public Entity
{
	//dung thuoc tinh direction lam stair direction // 1 = right, -1 = left
public:
	Stairs(float posX, float posY, int stairDirection = 1);
	~Stairs();

	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

