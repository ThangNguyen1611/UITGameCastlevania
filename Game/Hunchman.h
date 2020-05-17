#pragma once
#include "Entity.h"
#include "Timer.h"

#define HUNCHMAN_WALKING_SPEED			0.2f
#define HUNCHMAN_JUMP_SPEED_Y			0.2f
#define HUNCHMAN_HIGHJUMP_SPEED_Y		0.35f
#define HUNCHMAN_GRAVITY				0.002f

#define HUNCHMAN_BBOX_WIDTH				32
#define HUNCHMAN_BBOX_HEIGHT			32

#define HUNCHMAN_STATE_ACTIVE			0
#define HUNCHMAN_STATE_DIE				-1

#define HUNCHMAN_WAITING_TIME			900
#define HUNCHMAN_REACT_DELAY			450
#define HUNCHMAN_JUMP_TIME				150
#define HUNCHMAN_WAIT_JUMP_TIME			600

class Hunchman : public Entity
{
	LPGAMEENTITY target;
	bool targetDetected;
	bool activated;
	Timer* readyTimer = new Timer(HUNCHMAN_WAITING_TIME);
	bool targetSwitchDirection;
	Timer* reactTimer = new Timer(HUNCHMAN_REACT_DELAY);	
	//Them 1 khoang delay nho cho phan ung cua hunchman khi player doi huong
	bool isJumping, triggerJump;
	Timer* jumpingTimer = new Timer(HUNCHMAN_JUMP_TIME);
	Timer* waitingJumpTimer = new Timer(HUNCHMAN_WAIT_JUMP_TIME);

public:
	Hunchman(float posX, float posY, LPGAMEENTITY target);
	~Hunchman();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void TurnAround();
	void ShortJump();
	void LongJump();
};

