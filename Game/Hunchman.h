#pragma once
#include "Entity.h"
#include "Timer.h"

#define HUNCHMAN_JUMP_SPEED_X			0.275f
#define HUNCHMAN_JUMP_SPEED_Y			0.25f
#define HUNCHMAN_HIGHJUMP_SPEED_X		0.135f
#define HUNCHMAN_HIGHJUMP_SPEED_Y		0.55f
#define HUNCHMAN_JUMP_DISTANCE			70
#define HUNCHMAN_DODGEJUMP_SPEED_X		0.135f
#define HUNCHMAN_DODGEJUMP_SPEED_Y		0.4f
#define HUNCHMAN_MAX_HEIGHT_HIGHJUMP	350
#define HUNCHMAN_GRAVITY				0.002f
#define HUNCHMAN_MAXHEALTH				1
#define HUNCHMAN_CLOSE_TARGET_RANGE		100
#define HUNCHMAN_SIGHT_DODGE_RANGE		150
#define HUNCHMAN_SIGHT_RANGE			250
#define HUNCHMAN_SCORE_GIVEN			2000

#define HUNCHMAN_BBOX_WIDTH				32
#define HUNCHMAN_BBOX_HEIGHT			32

#define HUNCHMAN_STATE_ACTIVE			0
#define HUNCHMAN_STATE_DIE				-1

#define HUNCHMAN_WAITING_DURATION		1000
#define HUNCHMAN_REACT_DELAY			500
#define HUNCHMAN_JUMP_COOLDOWN			250

class Hunchman : public Entity
{
	LPGAMEENTITY target;
	bool targetDetected;
	bool activated;
	Timer* readyTimer = new Timer(HUNCHMAN_WAITING_DURATION);
	bool targetSwitchDirection;
	Timer* reactTimer = new Timer(HUNCHMAN_REACT_DELAY);	
	//Them 1 khoang delay nho cho phan ung cua hunchman khi player doi huong
	bool isJumping, triggerJump;
	Timer* waitingJumpTimer = new Timer(HUNCHMAN_JUMP_COOLDOWN);
	bool triggerWaitingJump;

public:
	Hunchman(float posX, float posY, LPGAMEENTITY target);
	~Hunchman();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void TurnAround();
	void Jump(float vX, float vY);
	bool IsObstacleAbove(vector<LPGAMEENTITY> *coObjects);
};

