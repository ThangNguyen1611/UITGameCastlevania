#pragma once
#include "Entity.h"
#include "Timer.h"

#define KNIGHT_WALKING_SPEED_X			0.06f
#define KNIGHT_GRAVITY					0.002f
#define KNIGHT_MAXHEALTH				3
#define KNIGHT_SCORE_GIVEN				1000

#define KNIGHT_BBOX_WIDTH				32
#define KNIGHT_BBOX_HEIGHT				62
#define KNIGHT_ARTICULATOR_POS_X		10

#define KNIGHT_STATE_WALKING			0
#define KNIGHT_STATE_DIE				-1
#define KNIGHT_STATE_HURTING			1

#define KNIGHT_HURT_DELAY				175

class Knight : public Entity
{
	float startX;
	float maxAmplitudeX;	//Bien do toi da cho phep di
	bool triggerHurting;
	Timer* hurtingTimer = new Timer(KNIGHT_HURT_DELAY);
	//Extension
	bool randomTurnaround;
public:
	Knight(float posX, float posY, int directionX, float maxAmplitudeX = 2000);
	~Knight();
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);

	void TurnAround();
	void TriggerHurt(bool b) { triggerHurting = b; }
};

