#pragma once
#include "Entity.h"
#include "Timer.h"

class Item;
typedef Item* LPGAMEITEM;

class Item : public Entity
{
protected:
	bool isDone;
	Timer* displayTimer;
	//bool finishedDelay;
	//Timer* delayTimer;
	DWORD delayStart;
	DWORD delayLimit;
public:
	Item();
	~Item();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	virtual void Render();

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
};

