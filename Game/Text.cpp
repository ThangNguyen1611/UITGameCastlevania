#include "Text.h"

Text::Text(){}

Text::~Text(){}

void Text::Render(float posX, float posY, const string &str)
{
	for (UINT i = 0; i < str.size(); i++)
	{
		//Hien tai chi dung so'
		if (str[i] >= '0' && str[i] <= '9')
		{
			textSpr = CSprites::GetInstance()->Get(str[i] - '0' + 84);
		}
		else	//va dau tru	
		{
			textSpr = CSprites::GetInstance()->Get(94);
		}
		textSpr->Draw(-1, posX + i * 15, posY);
	}
}

string Text::FillZeroString(string str, UINT MaxStringLenght)
{
	while (str.size() < MaxStringLenght)
		str = "0" + str;
	return str;
}
