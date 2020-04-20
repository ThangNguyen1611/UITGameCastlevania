#include "Text.h"

Text::Text()
{
	this->textTexture = Texture2dManager::GetInstance()->GetTexture(EntityType::TEXTS);
	this->textSprite = new Sprite(textTexture, MaxFrameRate);
}

Text::~Text(){}

void Text::Render(float posX, float posY, const string &str)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		//Hien tai chi dung so'
		if (str[i] >= '0' && str[i] <= '9')
		{
			textSprite->SelectFrame(str[i] - '0' + 26);
		}
		else	//va dau tru	
		{
			textSprite->SelectFrame(36);
		}
		textSprite->Draw(posX + i * textTexture->getFrameWidth(), posY);
	}
}

string Text::FillZeroString(string str, UINT MaxStringLenght)
{
	while (str.size() < MaxStringLenght)
		str = "0" + str;
	return str;
}
