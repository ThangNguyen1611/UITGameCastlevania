#include "UI.h"

UI::UI(int initPlayerHB, int initBossHealth)
{
	UITexture = Texture2dManager::GetInstance()->GetTexture(EntityType::BLACKBOARD);
	UISprite = new Sprite(UITexture, MaxFrameRate);

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
	UISprite->Draw(posX, posY);

	playerHB->Render();
	bossHB->Render();

	if (playerInfo->GetPlayerSupWeaponType() == EntityType::DAGGER)
	{
		playerSubWeaponSprite = new Sprite(Texture2dManager::GetInstance()->GetTexture(EntityType::ITEMDAGGER), MaxFrameRate);
		playerSubWeaponSprite->Draw(posX + 68, posY + 8);
	}

	text.Render(this->posX - 140, this->posY - 20, text.FillZeroString(to_string(playerInfo->GetScore()), MAX_TEXTLENGHT_SCORE));
	text.Render(this->posX + 50, this->posY - 20, text.FillZeroString(to_string(remainingTime), MAX_TEXTLENGHT_REMAININGTIME));
	text.Render(this->posX + 220, this->posY - 20, text.FillZeroString(to_string(currentStage), MAX_TEXTLENGHT_STAGE));
	text.Render(this->posX + 145, this->posY , text.FillZeroString(to_string(playerInfo->GetMana()), MAX_TEXTLENGHT_MANA));
	text.Render(this->posX + 145, this->posY + 18, text.FillZeroString(to_string(playerInfo->GetLive()), MAX_TEXTLENGHT_LIVE));

}
