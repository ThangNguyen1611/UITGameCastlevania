#pragma once
#include "Item.h"

#define CROWN_GRAVITY				0.1f
#define CROWN_PUSHUP_SPEED_Y		0.02f
#define CROWN_PUSH_UP_DISTANCE		48
#define CROWN_SCORE_GIVEN			1000

#define CROWN_DISPLAY_DURATION		9000
#define CROWN_DELAY					100

class Crown : public Item
{
	bool isShowDone;
	float destinationY;
public:
	Crown(float posX, float posY);
	~Crown();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
};

