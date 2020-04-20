#pragma once
#include "Texture2d.h"
#include "Camera.h"

class Sprite
{
	int currentFrame, totalFrame;
	float timePerFrame, currentTotalTime;
	Texture2d* texture;
	LPD3DXSPRITE spriteHandler;

public:
	Sprite(Texture2d* TEXTURE, float TIMEPERFRAME = 0.1f);	//Khong chinh timeperframe cho moi ani duoc
	~Sprite();

	void Update(DWORD dt);
	void Draw(float posX, float posY, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void DrawFlipVertical(float posX, float posY, int alpha = 255, int R = 255, int G = 255, int B = 255);
	void Draw1Frame(int idFrame, float posX, float posY, int alpha = 255, int R = 255, int G = 255, int B = 255);

	RECT GetRectFrame(int CURRENTFRAME);

	int GetCurrentFrame() { return currentFrame; }
	void SetCurrentTotalTime(float value) { currentTotalTime = value; }
	float GetCurrentTotalTime() { return currentTotalTime; }
	void SelectFrame(int idFrame) { currentFrame = idFrame; }
};

