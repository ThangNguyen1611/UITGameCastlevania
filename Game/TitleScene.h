#pragma once
#include "Scene.h"
#include "Texture2dManager.h"
#include "Sprite.h"

#define BAT_ANI_BEGIN			0
#define BAT_ANI_START_LOOP		12
#define BAT_ANI_END				14

#define BAT_FLAPPING_SPEED		150

#define STARTTEXT_BEGIN			0
#define STARTTEXT_END			1

#define STARTTEXT_TRANS_SPEED	200

class TitleScene : public Scene
{
	Texture2d* screenTexture;
	Sprite* screenSprite;
	Texture2d* batTexture;
	Sprite* batSprite;
	Texture2d* startTexture;
	Sprite* startSprite;

	bool isAllowToStart;
public:
	TitleScene();

	void Load();
	void Update(DWORD dt);
	void Render();
	void Unload();

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




