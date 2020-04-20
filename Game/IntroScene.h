#pragma once
#include "Scene.h"
#include "Texture2dManager.h"
#include "Sprite.h"
#include "Timer.h"

#define SIMON_WALKING_SPEED				0.15f

#define SIMON_ANI_IDLE_START			0
#define SIMON_ANI_WALKING_BEGIN			1
#define SIMON_ANI_WALKING_END			3
#define SIMON_ANI_IDLE_END				9

#define SIMON_TRANS_SPEED				120

#define SIMON_BEGIN_WALK_DELAY			1500
#define SIMON_END_WALK_DELAY			2000

class IntroScene : public Scene
{
	Texture2d* screenTexture;
	Sprite* screenSprite;

	//Co the lam 1 class cho introSimon ke thua Entity, nhung that su chi can 4 thuoc tinh nay de lam introSimon
	Texture2d* introSimonTexture;
	Sprite* introSimonSprite;
	float introSimonPosX, introSimonPosY;

	//Phase 1
	DWORD timeBeginSimonDelay,
		timeBeginSimonDelayMax;

	Timer* timerEndSimonDelay = new Timer(SIMON_END_WALK_DELAY);	
	//Khac nhau giua timer va DWORD o tren la Timer can dieu kien kich hoat, DWORD thi bat dau ngay tu khi tao ra
	bool isDelayPhase1End;
	bool isAllowToPlayPhase1;
	//Phase 2
	bool triggerStartPhase2;
	bool isAllowToPlayPhase2;
	bool isGoingOutside;
	//Phase 3
	bool isAllowToPlayPhase3;

	bool triggerPlay;
public:
	IntroScene();

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();

	friend class IntroScenceKeyHandler;
};


class IntroScenceKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroScenceKeyHandler(Scene *s) :ScenceKeyHandler(s) {};
};




