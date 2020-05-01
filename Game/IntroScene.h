#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animations.h"
#include "Timer.h"

#define SIMON_WALKING_SPEED				0.15f

#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALKING				1
#define SIMON_STATE_IDLE_END			2

#define SIMON_BEGIN_WALK_DELAY			1500
#define SIMON_END_WALK_DELAY			2000

class IntroScene : public Scene
{
	LPSPRITE introSceneSpr;
	LPANIMATION_SET simonAniSet;

	int simonState;
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

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
public:
	IntroScene();

	void LoadSceneObjects();
	void Update(DWORD dt);
	void Render();
	void Unload();

	void LoadBaseTextures();
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




