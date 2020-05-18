#include "UI.h"

UI::UI(int initPlayerHB, int initBossHealth)
{
	UIanimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_BLACKBOARD);

	playerHB = new HealthBar(initPlayerHB, true);
	bossHB = new HealthBar(initBossHealth, false);
}

UI::~UI(){}

void UI::Update(float posX, float posY, int currentPlayerHealth, int currentBossHealth)
{
	this->posX = posX;
	this->posY = posY;

	playerHB->Update(currentPlayerHealth, posX - 140, posY);
	bossHB->Update(currentBossHealth, posX - 140, posY + 20);
}

void UI::Render(int currentStage, int remainingTime, Player* playerInfo)
{
	UIanimationSet->at(0)->Render(-1, posX , posY);

	playerHB->Render();
	bossHB->Render();

	if (playerInfo->IsGettingDouble())
	{
		UIExtraShot = CSprites::GetInstance()->Get(95);
		UIExtraShot->Draw(-1, this->posX + 210, this->posY + 12);
	}
	else if (playerInfo->IsGettingTriple())
	{
		UIExtraShot = CSprites::GetInstance()->Get(96);
		UIExtraShot->Draw(-1, this->posX + 210, this->posY + 12);
	}

	if (playerInfo->GetPlayerSupWeaponType() == EntityType::DAGGER)
	{
		playerSubWeaponAnimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMDAGGER);
		playerSubWeaponAnimationSet->at(0)->Render(1, posX + 68, posY + 8);
	}
	if (playerInfo->GetPlayerSupWeaponType() == EntityType::BOOMERANG)
	{
		playerSubWeaponAnimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMBMR);
		playerSubWeaponAnimationSet->at(0)->Render(1, posX + 68, posY + 8);
	}
	if (playerInfo->GetPlayerSupWeaponType() == EntityType::AXE)
	{
		playerSubWeaponAnimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMAXE);
		playerSubWeaponAnimationSet->at(0)->Render(1, posX + 68, posY + 8);
	}
	if (playerInfo->GetPlayerSupWeaponType() == EntityType::WATERPOTION)
	{
		playerSubWeaponAnimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMWATERPOTION);
		playerSubWeaponAnimationSet->at(0)->Render(1, posX + 68, posY + 8);
	}
	if (playerInfo->GetPlayerSupWeaponType() == EntityType::STOPWATCH)
	{
		playerSubWeaponAnimationSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_ITEMSTOPWATCH);
		playerSubWeaponAnimationSet->at(0)->Render(1, posX + 68, posY + 8);
	}

	text.Render(this->posX - 140, this->posY - 20, text.FillZeroString(to_string(playerInfo->GetScore()), MAX_TEXTLENGHT_SCORE));
	text.Render(this->posX + 50, this->posY - 20, text.FillZeroString(to_string(remainingTime), MAX_TEXTLENGHT_REMAININGTIME));
	text.Render(this->posX + 220, this->posY - 20, text.FillZeroString(to_string(currentStage), MAX_TEXTLENGHT_STAGE));
	text.Render(this->posX + 145, this->posY , text.FillZeroString(to_string(playerInfo->GetMana()), MAX_TEXTLENGHT_MANA));
	text.Render(this->posX + 145, this->posY + 18, text.FillZeroString(to_string(playerInfo->GetLive()), MAX_TEXTLENGHT_LIVE));

}
