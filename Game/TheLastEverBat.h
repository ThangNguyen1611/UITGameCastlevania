#pragma once
#include "Entity.h"

#define TLEBAT_MAXHEALTH					16
#define TLEBAT_DAMAGE						3
#define TLEBAT_SCORE_GIVEN					10000
#define TLEBAT_MIN_POS_X					1040
#define TLEBAT_MAX_POS_X					1500
#define TLEBAT_MIN_POS_Y					150
#define TLEBAT_MAX_POS_Y					450
#define TLEBAT_POS_Y_AMPLITUDE_CALC			400

#define TLEBAT_GO_PRESET_LOCATION_SPEED		1.25
#define TLEBAT_GO_STAIR						1
#define TLEBAT_GO_TALLTOWER					2
#define TLEBAT_GO_WINDOW					3
#define TLEBAT_GO_SHORTTOWER				4
#define TLEBAT_AT_STAIR_POS_X				1425
#define TLEBAT_AT_STAIR_POS_Y				300
#define TLEBAT_AT_TALLTOWER_POS_X			1175
#define TLEBAT_AT_TALLTOWER_POS_Y			275
#define TLEBAT_AT_WINDOW_POS_X				1425
#define TLEBAT_AT_WINDOW_POS_Y				200
#define TLEBAT_AT_SHORTTOWER_POS_X			1300
#define TLEBAT_AT_SHORTTOWER_POS_Y			275

#define TLEBAT_CURVE_FLY_SPEED_X			0.265
#define TLEBAT_CURVE_FLY_SPEED_Y			0.008

#define TLEBAT_BBOX_WIDTH					96
#define TLEBAT_BBOX_HEIGHT					54

#define TLEBAT_STATE_DIE					-1
#define TLEBAT_STATE_INACTIVE				0
#define TLEBAT_STATE_FLYING					1

#define TLEBAT_WAITING_DURATION				2000
#define TLEBAT_FLY_CURVE_DURATION			2000

class TheLastEverBat : public Entity
{
	bool activated;
	bool isDonePhaseWait;
	bool isDoneFlyCurve,
		isGetDistanceYTarget;
	float distanceYTarget;
	LPGAMEENTITY target;
	int directionY;
	float randomXTarget, randomYTarget;
	int process;

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

	void FlyStyle(float currentPosY, float extendSpeedX = 0, float extendSpeedY = 0);
};

