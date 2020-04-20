#pragma once
#include "Weapon.h"

#define DAGGER_SPEED_X		0.4f

#define MAX_DAGGER_DELAY		220		//2 times simon's ani attack

class Dagger : public Weapon
{
	float ownerPosX;
	float timeDelayed, timeDelayMax;
public:
	Dagger();
	~Dagger();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	void Attack(float posX, float posY, int direction);

	bool CheckIsOutCamera(float posX);

	void ResetDelay() { timeDelayed = 0; }
};

