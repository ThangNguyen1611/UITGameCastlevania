#include "Texture2d.h"

Texture2d::Texture2d(char* filePath, int TOTALFRAME, int FRAMEWIDTH, int FRAMEHEIGHT, D3DCOLOR colorKey, int left, int top, int right, int bottom)
{
	this->totalFrame = TOTALFRAME;	//that ra khong can vi tinh duoc = totalColumn * totalRow
	frameWidth = FRAMEWIDTH;
	frameHeight = FRAMEHEIGHT;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);

	totalColumn = info.Width / frameWidth;
	totalRow = info.Height / frameHeight;

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	result = D3DXCreateTextureFromFileExA(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&info,
		NULL,
		&Texture);							// Created textTexture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
}

Texture2d::~Texture2d() 
{
	if (this->Texture != NULL)
		this->Texture->Release();
}
