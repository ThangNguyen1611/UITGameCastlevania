#pragma once
#include "Entity.h"

class Weapon : public Entity
{
protected:
	bool isDone;
public:
	Weapon();
	~Weapon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	virtual void Render();

	virtual void Attack(float posX, float posY, int direction);
	virtual void ArticulatedPlayerPos(bool isSitting) {}

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }

	virtual bool IsCollidingObject(Entity* Obj);	//Not inherit from Entity cause this func return the result from Entity
};

