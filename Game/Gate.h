#pragma once
#include "Entity.h"

#define GATE_BBOX_WIDTH				48
#define GATE_BBOX_HEIGHT			96

#define GATE_ANI_BASIC_FORM			0

class Gate : public Entity
{
	int gateSwitchSceneId;	//Gate nay se dan~ den scene nao
public:
	Gate(float posX, float posY, int switchId);
	~Gate();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = NULL);
	void Render();

	int GetIdScene() { return gateSwitchSceneId; }
};

