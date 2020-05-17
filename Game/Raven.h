#pragma once
#include "Entity.h"

#define RAVEN_FLYING_SPEED_PHASE1			1.25f	//Fly after Inactive
#define RAVEN_FLYING_SPEED_PHASE2			3.0f	//Fly after Waiting
#define RAVEN_FLYING_SPEED_PHASE3			5.0f	//Fly Toward when close enough
#define RAVEN_FLYING_SPEED_Y_PHASE1			0.02f
#define RAVEN_DIST_TO_DEST_POSX_PHASE1		-75		//Distance to Destination to end state Waiting
#define RAVEN_DIST_TO_DEST_POSY_PHASE1		100
#define RAVEN_DIST_TO_DEST_POSX_PHASE2		-90
#define RAVEN_DIST_TO_DEST_POSY_PHASE2		-60

#define RAVEN_BBOX_WIDTH					32
#define RAVEN_BBOX_HEIGHT					32

#define RAVEN_STATE_INACTIVE				0
#define RAVEN_STATE_FLYING					1
#define RAVEN_STATE_DIE						-1

#define RAVEN_WAITING_TIME					600
#define RAVEN_READY_TIME_TO_ATTACK			3600

class Raven : public Entity
{
	bool activated;
	float destinationPosXPhase1,
		destinationPosYPhase1; 
	bool isDonePhase1;
	float destinationPosXPhase2,
		destinationPosYPhase2;
	bool isDonePhase2;
	int sidePhase2;
	int countChangeSide;
	bool triggerReady;
	bool isRavenTired;
	float destinationPosXRavenTired,
		destinationPosYRavenTired;

	LPGAMEENTITY target;

	Timer* waitingTimer = new Timer(RAVEN_WAITING_TIME);
	Timer* readyTimer = new Timer(RAVEN_READY_TIME_TO_ATTACK);
public:
	Raven(float posX, float posY, int directionX, LPGAMEENTITY target);
	~Raven();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
};

