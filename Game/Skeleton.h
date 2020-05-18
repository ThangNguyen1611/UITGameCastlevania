#pragma once
#include "Entity.h"
#include "Timer.h"
#include "Bone.h"

#define SKELETON_WALKING_SPEED			0.165f
#define SKELETON_JUMP_SPEED_Y			0.25f
#define SKELETON_FIRST_JUMP_SPEED_Y		0.65f
#define SKELETON_GRAVITY				0.002f

#define SKELETON_BBOX_WIDTH				32
#define SKELETON_BBOX_HEIGHT			62

#define SKELETON_STATE_ACTIVE			0
#define SKELETON_STATE_DIE				-1

#define SKELETON_WAITING_TIME			900
#define SKELETON_REACT_DELAY			450
#define SKELETON_JUMP_TIME				265
#define SKELETON_WAIT_JUMP_TIME			900

class Skeleton : public Entity
{
	LPGAMEENTITY target;
	bool targetDetected;
	bool activated;
	Timer* readyTimer = new Timer(SKELETON_WAITING_TIME);
	bool targetSwitchDirection;
	Timer* reactTimer = new Timer(SKELETON_REACT_DELAY);
	//Them 1 khoang delay nho cho phan ung cua skeleton khi player doi huong
	bool isJumping, triggerJump;
	Timer* jumpingTimer = new Timer(SKELETON_JUMP_TIME);
	Timer* waitingJumpTimer = new Timer(SKELETON_WAIT_JUMP_TIME);
	int randomJump;

	Bone* mainWeapon;
	bool triggerResetDelay;
public:
	Skeleton(float posX, float posY, LPGAMEENTITY target);
	~Skeleton();

	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void TurnAround();
	void Jump();
	void JumpBack();
	void FirstJump();
	void Attack();

	Bone* GetBone() { return mainWeapon; }
};

