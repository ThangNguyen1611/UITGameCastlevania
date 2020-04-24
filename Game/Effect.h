#pragma once
#include "Animations.h"

class Effect;
typedef Effect* LPGAMEEFFECT;

class Effect
{
protected:
	float posX, posY;
	bool isDone;
	LPANIMATION_SET animationSet;
public:
	Effect();
	~Effect();

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	bool GetIsDone() { return isDone; }
	void SetIsDone(bool isdone) { isDone = isdone; }
	void SetAnimationSet(LPANIMATION_SET aniSet) { animationSet = aniSet; }
	LPANIMATION_SET GetAniSet() { return animationSet; }
};

