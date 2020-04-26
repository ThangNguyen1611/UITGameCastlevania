#pragma once
#include "Entity.h"

class Weapon : public Entity
{
protected:
	bool isDone;
	bool isReceivedPos;
	bool isDidDamage;
public:
	Weapon();
	~Weapon();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	virtual void Render();

	virtual void Attack(float posX, int direction);
	virtual void ArticulatedPlayerPos(bool isSitting) {}

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }

	bool GetIsReceivedPos() { return isReceivedPos; }
	void SetIsReceivedPos(bool istime) { isReceivedPos = istime; }

	bool GetIsDidDamage() { return isDidDamage; }
	void SetIsDidDamage(bool isDid) { isDidDamage = isDid; }

	virtual bool IsCollidingObject(Entity* Obj);	//Not inherit from Entity cause this func return the result from Entity
};

