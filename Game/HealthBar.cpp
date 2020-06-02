#include "HealthBar.h"

HealthBar::HealthBar(int maxHealth, bool isAllies)
{
	currentOwnerHealth = maxHealth;
	maxOwnerHealth = maxHealth;
	this->isAllies = isAllies;

	for (int i = 0; i < currentOwnerHealth; i++) 
	{
		LPANIMATION_SET aniSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYERHP);
		health.push_back(aniSet);
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
}

void HealthBar::Render()
{
	if (currentOwnerHealth <= 0)
		return;
	else
	{
		for (int j = 0; j < currentOwnerHealth; j++)
		{
			if (isAllies)
			{
				health[j]->at(HEALTH_TYPE_PLAYER_HAVE)->Render(-1, posX + j * HEALTH_SPACE_UNIT, posY);
			}
			else
			{
				health[j]->at(HEALTH_TYPE_ENEMY_HAVE)->Render(-1, posX + j * HEALTH_SPACE_UNIT, posY);
			}
		}
		for (int l = currentOwnerHealth; l < maxOwnerHealth; l++)
		{
			health[l]->at(HEALTH_TYPE_PLAYER_LOST)->Render(-1, posX + l * HEALTH_SPACE_UNIT, posY);
		}
	}
}
