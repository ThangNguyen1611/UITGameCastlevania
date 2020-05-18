#pragma once
#include "Entity.h"

class Weapon : public Entity
{
protected:
	bool isDone;
	bool isReceivedPos;
	float timeDelayed, timeDelayMax;
	int damage;
public:
	Weapon();
	~Weapon();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	virtual void Render();

	virtual void Attack(float posX, int direction);
	virtual void ArticulatedPlayerPos(bool isSitting) {}

	void ResetDelay() { timeDelayed = 0; }
	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	int GetDamage() { return damage; }

	bool GetIsReceivedPos() { return isReceivedPos; }
	void SetIsReceivedPos(bool istime) { isReceivedPos = istime; }

	bool CheckIsOutCamera(float posX);
	virtual bool IsCollidingObject(Entity* Obj);	//Not inherit from Entity cause this func return the result from Entity
};

