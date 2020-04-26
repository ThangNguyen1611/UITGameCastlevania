#pragma once
#include "Item.h"

#define CROWN_GRAVITY				0.03f
#define CROWN_PUSHUP_SPEED			0.02f

#define CROWN_TIMEDISPLAYMAX		9000
#define CROWN_TIMEDELAYMAX			100

class Crown : public Item
{
	bool isShowDone;
public:
	Crown(float posX, float posY);
	~Crown();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
};

