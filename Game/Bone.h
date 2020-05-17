#pragma once
#include "Weapon.h"
#include <math.h>

#define BONE_SPEED_X					0.2f	
#define BONE_SPEED_Y					0.02f	
#define BONE_MAX_DISTANCE_HEIGHT		50		

#define BONE_BBOX_WIDTH					32
#define BONE_BBOX_HEIGHT				32

#define MAX_BONE_DELAY					260		

class Bone : public Weapon
{
	float tempY;
	int directionY;
	bool isDidDamage;
public:
	Bone();
	~Bone();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, int direction);
	bool IsCollidingObject(Entity* Obj);	//Make Bone do 1 damage truely
};
