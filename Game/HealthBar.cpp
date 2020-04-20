#include "HealthBar.h"

HealthBar::HealthBar(int maxHealth, bool isAllies)
{
	currentOwnerHealth = maxHealth;
	maxOwnerHealth = maxHealth;
	this->isAllies = isAllies;

	for (int i = 0; i < currentOwnerHealth; i++) {
		Texture2d* TextureStackHealth = Texture2dManager::GetInstance()->GetTexture(EntityType::PLAYERHP);
		Sprite* spriteStackHealth = new Sprite(TextureStackHealth, MaxFrameRate);
		health.push_back(spriteStackHealth);
	}
}

HealthBar::~HealthBar() {}

void HealthBar::Update(int currentHealth, float X, float Y)
{
	currentOwnerHealth = currentHealth;
	if (currentOwnerHealth <= 0)
		return;
	posX = X;
	posY = Y;
	if(isAllies)
		for (int i = 0; i < maxOwnerHealth; i++) {
			for (int j = 0; j < currentOwnerHealth; j++) {
				health[j]->SelectFrame(HEALTH_STATE_HAVE);
			}
			for (int l = currentOwnerHealth; l < maxOwnerHealth; l++) {
				health[l]->SelectFrame(HEALTH_STATE_LOST);
			}
		}
	else
		for (int i = 0; i < maxOwnerHealth; i++) {
			for (int j = 0; j < currentOwnerHealth; j++) {
				health[j]->SelectFrame(HEALTH_STATE_ENEMY_HAVE);
			}
			for (int l = currentOwnerHealth; l < maxOwnerHealth; l++) {
				health[l]->SelectFrame(HEALTH_STATE_LOST);
			}
		}
}

void HealthBar::Render()
{
	if (currentOwnerHealth <= 0)
		return;
	else
		for (int i = 0; i < maxOwnerHealth; i++) {
			health[i]->Draw(posX + i * 10, posY);
		}
}
