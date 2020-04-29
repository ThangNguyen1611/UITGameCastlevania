#pragma once
#include "Weapon.h"

#define DAGGER_SPEED_X		0.4f

#define DAGGER_BBOX_WIDTH		32
#define DAGGER_BBOX_HEIGHT		18

#define MAX_DAGGER_DELAY		260		//2 times simon's ani attack

class Dagger : public Weapon
{
	float ownerPosX;
public:
	Dagger();
	~Dagger();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, int direction);


};

