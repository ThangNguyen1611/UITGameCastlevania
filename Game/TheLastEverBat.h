#pragma once
#include "Entity.h"

#define TLEBAT_MAXHEALTH					16
#define TLEBAT_DAMAGE						3
#define TLEBAT_SCORE_GIVEN					10000
#define TLEBAT_MIN_POS_X					1040
#define TLEBAT_MAX_POS_X					1500
#define TLEBAT_MIN_POS_Y					100
#define TLEBAT_MAX_POS_Y					450

#define TLEBAT_GO_WINDOW_SPEED				1.25
#define TLEBAT_AT_WINDOW_POS_X				1425
#define TLEBAT_AT_WINDOW_POS_Y				300
#define TLEBAT_NOTAT_WINDOW_POS_X			1175
#define TLEBAT_NOTAT_WINDOW_POS_Y			275

#define TLEBAT_CURVE_FLY_SPEED_X			0.265
#define TLEBAT_CURVE_FLY_SPEED_Y			0.008

#define TLEBAT_BBOX_WIDTH					96
#define TLEBAT_BBOX_HEIGHT					46

#define TLEBAT_STATE_DIE					-1
#define TLEBAT_STATE_INACTIVE				0
#define TLEBAT_STATE_FLYING					1

#define TLEBAT_WAITING_DURATION				2000
#define TLEBAT_FLY_CURVE_DURATION			2000

class TheLastEverBat : public Entity
{
	bool activated;
	bool isPhaseWaitAtWindow,
		isDonePhaseWait;
	bool isDoneFlyCurve,
		isGetDistanceYTarget;
	float distanceXTarget;
	LPGAMEENTITY target;
	int directionY;

	bool isStartFlyCurve;
	Timer* flyCurveTimer = new Timer(TLEBAT_FLY_CURVE_DURATION);
public:
	bool waitingTrigger;
	Timer* waitingTimer = new Timer(TLEBAT_WAITING_DURATION);

	TheLastEverBat(float posX, float posY, LPGAMEENTITY target);
	~TheLastEverBat();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

};

