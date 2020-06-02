#pragma once
#include "Item.h"

#define EXTRASHOT_GRAVITY			0.03f

#define EXTRASHOT_DISPLAY_DURATION	4500
#define EXTRASHOT_DELAY				100

class ExtraShot : public Item
{
	int typeExtraShot; //2 = double, 3 = triple
public:
	ExtraShot(float posX, float posY, int type);
	~ExtraShot();

	void Render();

	int GetTypeExtra() { return typeExtraShot; }
};

