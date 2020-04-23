#pragma once
#include "Entity.h"

#define CANDLE_BBOX_WIDTH		16
#define CANDLE_BBOX_HEIGHT		32

class Candle : public Entity
{
	int idCandle; //dung de xac dinh item rot stage 1
public:
	Candle(float posX, float posY, int id = 1);
	~Candle();

	void Update(DWORD dt, vector<LPGAMEENTITY> *coObjects = 0);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetIdCandle() { return idCandle; }
};



