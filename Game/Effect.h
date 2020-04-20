#pragma once
#include "Texture2dManager.h"
#include "Sprite.h"

class Effect;
typedef Effect* LPGAMEEFFECT;

class Effect
{
protected:
	float posX, posY;
	bool isDone;
	Texture2d* texture;
	Sprite* sprite;
public:
	Effect();
	~Effect();

	virtual void Update(DWORD dt);
	virtual void Render();

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
};

