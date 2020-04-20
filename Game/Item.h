#pragma once
#include "Entity.h"

class Item;
typedef Item* LPGAMEITEM;

class Item : public Entity
{
protected:
	bool isDone;
	DWORD	timeDisplayed,
			timeDisplayMax;		//duoc define rieng
	DWORD	timeDelayDisplayed,
			timeDelayDisplayMax;
public:
	Item();
	~Item();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	virtual void Render();

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
};

