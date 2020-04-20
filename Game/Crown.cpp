#include "Crown.h"

Crown::Crown(float posX, float posY)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::CROWN);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::CROWN;

	this->posX = posX;
	this->posY = posY;

	timeDisplayed = 0;
	timeDisplayMax = CROWN_TIMEDISPLAYMAX;
	timeDelayDisplayed = 0;
	timeDelayDisplayMax = CROWN_TIMEDELAYMAX;
	isShowDone = false;
}

Crown::~Crown() {}

void Crown::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	//Do kha nang moc. tu dat' len nen khong the dung lai item::update

	//thoat khoi tinh trang doi
	timeDelayDisplayed += dt;
	if (timeDelayDisplayed < timeDelayDisplayMax)
	{
		return;
	}
	timeDisplayed += dt;
	if (timeDisplayed >= timeDisplayMax)	//xong trach nhiem
	{
		isDone = true;
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (currentFrame < CROWN_ANI_BEGIN)
	{
		sprite->SelectFrame(CROWN_ANI_BEGIN);
		sprite->SetCurrentTotalTime(dt);
	}
	else {
		sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
		if (sprite->GetCurrentTotalTime() >= CROWN_TWINKLE_SPEED)
		{
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - CROWN_TWINKLE_SPEED);
			sprite->SelectFrame(currentFrame + 1);
		}

		if (sprite->GetCurrentFrame() > CROWN_ANI_END) {
			sprite->SelectFrame(CROWN_ANI_BEGIN);
		}
	}

	Entity::Update(dt);

	if (isShowDone)
	{
		vY = CROWN_GRAVITY;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		vector<LPGAMEENTITY> bricks;

		coEvents.clear();
		bricks.clear();
		for (UINT i = 0; i < coObjects->size(); i++)
			if (coObjects->at(i)->GetType() == EntityType::BRICK ||
				coObjects->at(i)->GetType() == EntityType::BREAKABLEBRICK)
				bricks.push_back(coObjects->at(i));

		CalcPotentialCollisions(&bricks, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			posY += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			posX += min_tx * dx + nx * 0.1f;
			posY += min_ty * dy + ny * 0.1f;

			if (ny == -1)
				vY = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
	else
	{
		vY = -CROWN_PUSHUP_SPEED;
		posY += dy;
		if (posY <= 409)
		{
			isShowDone = true;
		}
	}
}
