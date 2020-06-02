#pragma once
#include "Item.h"

#define CROWN_GRAVITY				0.03f
#define CROWN_PUSHUP_SPEED_Y		0.02f
#define CROWN_POS_Y_DESTINATION		409

#define CROWN_DISPLAY_DURATION		9000
#define CROWN_DELAY					100

class Crown : public Item
{
	bool isShowDone;
public:
	Crown(float posX, float posY);
	~Crown();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
};

