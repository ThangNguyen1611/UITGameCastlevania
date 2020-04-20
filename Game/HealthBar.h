#pragma once
#include "Texture2dManager.h"
#include "Sprite.h"

#include <vector>

#define HEALTH_STATE_HAVE			0
#define HEALTH_STATE_LOST			1
#define HEALTH_STATE_ENEMY_HAVE		2

class HealthBar
{
	float posX, posY; 
	int currentOwnerHealth, maxOwnerHealth;
	std::vector<Sprite*> health;
	bool isAllies;
public:
	HealthBar(int maxHealth, bool isAllies);
	~HealthBar();

	void Update(int currentHealth, float X, float Y);
	void Render();

	void SetPosition(float X, float Y) { posX = X; posY = Y; }
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	void ReceivePos(float &x, float &y) { x = this->posX; y = this->posY; }
	void SetPosX(float X) { posX = X; }
	void SetPosY(float Y) { posY = Y; }
};

