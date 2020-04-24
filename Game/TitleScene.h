#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Animations.h"

class TitleScene : public Scene
{
	LPSPRITE titleSceneSpr;
	LPANIMATION_SET batAniSet;
	LPANIMATION_SET startAniSet;

	bool isAllowToStart;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
public:
	TitleScene();

	void LoadSceneObjects();
	void Update(DWORD dt);
	void Render();
	void Unload();

	void LoadTextures();
	friend class TitleScenceKeyHandler;
};



class TitleScenceKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	TitleScenceKeyHandler(Scene *s) :ScenceKeyHandler(s) {};
};




