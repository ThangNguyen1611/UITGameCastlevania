#pragma once
#include "Entity.h"
#include "Text.h"
#include "HealthBar.h"
#include "Player.h"

using namespace std;

#define MAX_TEXTLENGHT_SCORE					6
#define MAX_TEXTLENGHT_REMAININGTIME			4
#define MAX_TEXTLENGHT_STAGE					2
#define MAX_TEXTLENGHT_MANA						2
#define MAX_TEXTLENGHT_LIVE						2

class UI
{
	float posX, posY;

	LPANIMATION_SET UIanimationSet;

	Text text;
	HealthBar* playerHB;
	HealthBar* bossHB;
	LPSPRITE UIExtraShot;
	LPANIMATION_SET playerSubWeaponAnimationSet;
public:
	UI(int initPlayerHealth = 16, int initBossHealth = 16);
	~UI();

	void Update(float posX, float posY, int currentPlayerHealth, int currentBossHealth);
	void Render(int currentStage, int remainingTime, Player* playerInfo);
};

