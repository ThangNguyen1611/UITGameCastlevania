#pragma once
#include "Effect.h"

#define EXPLODE_TYPE1					0
#define EXPLODE_TYPE2					1
#define EXPLODE_TYPE3					2
#define EXPLODE_TYPE4					3

#define EXPLODE_SPEED_X_TYPE1			0.07f
#define EXPLODE_SPEED_Y_TYPE1			0.02f
#define EXPLODE_SPEED_X_TYPE2			0.09f
#define EXPLODE_SPEED_Y_TYPE2			0.03f
#define EXPLODE_SPEED_X_TYPE3			0.06f
#define EXPLODE_SPEED_Y_TYPE3			0.02f
#define EXPLODE_SPEED_X_TYPE4			0.08f
#define EXPLODE_SPEED_Y_TYPE4			0.04f

#define EXPLODE_MAXHEIGHT_TYPE1			25
#define EXPLODE_MAXHEIGHT_TYPE2			50
#define EXPLODE_MAXHEIGHT_TYPE3			25
#define EXPLODE_MAXHEIGHT_TYPE4			70

class BrickExplode : public Effect
{
	int type;
	float tempY;
	float vX, vY;
	int direction, directionY;
public:
	BrickExplode(float posX, float posY, int type);
	~BrickExplode();

	void Update(DWORD dt);
	void Render();
};


