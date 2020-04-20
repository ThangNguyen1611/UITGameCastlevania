#pragma once
#include <Windows.h>

class Camera
{
	static Camera * __instance;
	float camPosX, camPosY;

	Camera();
	~Camera();
public:

	static Camera* GetInstance();

	void SetCamPos(float x, float y) { camPosX = x; camPosY = y; }
	float GetCamPosX() { return camPosX; }
	float GetCamPosY() { return camPosY; }
};

