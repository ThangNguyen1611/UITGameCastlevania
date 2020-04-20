#pragma once

#include "Game.h"

class Texture2d
{
	int left;
	int top;
	int right;
	int bottom;
	int totalColumn, totalRow, frameWidth, frameHeight;
	int totalFrame;
	LPDIRECT3DTEXTURE9 Texture;

public:
	Texture2d(char* filePath, int TOTALFRAME, int FRAMEWIDTH, int FRAMEHEIGHT, D3DCOLOR colorKey = NULL, int left = 0, int top = 0, int right = 0, int bottom = 0);
	~Texture2d();

	int getColumn() { return totalColumn; }
	int getRow() { return totalRow; }
	int getFrameWidth() { return frameWidth; }
	int getFrameHeight() { return frameHeight; }
	int GetTotalFrame() { return totalFrame; }

	int GetRectLeft() { return left; }
	int GetRectTop() { return top; }
	int GetRectRight() { return right; }
	int GetRectBottom() { return bottom; }

	LPDIRECT3DTEXTURE9 GetTexture() { return Texture; }
};

