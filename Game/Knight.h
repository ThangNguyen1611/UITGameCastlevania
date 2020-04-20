#pragma once
#include "Entity.h"

#define KNIGHT_WALKING_SPEED			0.06f
#define KNIGHT_GRAVITY					0.002f

#define KNIGHT_BBOX_WIDTH				40
#define KNIGHT_BBOX_HEIGHT				80

#define KNIGHT_STATE_WALKING			100
#define KNIGHT_STATE_DIE				200

#define KNIGHT_ANI_WALKING_BEGIN		0
#define KNIGHT_ANI_WALKING_END			2

#define KNIGHT_SWAPLEG_SPEED			200 

class Knight : public Entity
{
	float startX;
	float maxAmplitudeX;	//Bien do toi da cho phep di

	//Extension
	bool randomTurnaround;
public:
	Knight(float posX, float posY, int directionX, float maxAmplitudeX = 2000);
	~Knight();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void TurnAround();
};

