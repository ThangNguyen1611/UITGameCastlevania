#include "Bat.h"
#include <math.h>
#define PI 3.141562535898

Bat::Bat(float posX, float posY, int direction) 
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::BAT);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::BAT;

	this->posX = posX;
	this->posY = posY;
	tempY = posY;
	this->direction = direction;
	directionY = 1;

	this->SetState(BAT_STATE_FLYING);

	health = 1;
	isDead = false;
}

Bat::~Bat(){}

void Bat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 0 || posX > SCREEN_WIDTH * 2)
	{
		SetState(BAT_STATE_DIE);
		return;
	}

	int currentFrame = sprite->GetCurrentFrame();
	if (!isDead) 
	{
		if (currentFrame < BAT_ANI_FLYING_BEGIN) {
			sprite->SelectFrame(BAT_ANI_FLYING_BEGIN);
			sprite->SetCurrentTotalTime(dt);
		}
		else {
			sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() + dt);
			if (sprite->GetCurrentTotalTime() >= BAT_FLAPPING_SPEED) {
				sprite->SetCurrentTotalTime(sprite->GetCurrentTotalTime() - BAT_FLAPPING_SPEED);
				sprite->SelectFrame(sprite->GetCurrentFrame() + 1);			
			}

			if (sprite->GetCurrentFrame() > BAT_ANI_FLYING_END) {
				sprite->SelectFrame(BAT_ANI_FLYING_BEGIN);
			}
		}
	}
	
	//2 optional to FLY

	//zigzag one
	/*if (posY - tempY >= BAT_AMPLITUDE_HORIZONTAL)
		directionY = -1;
	else if(tempY - posY >= BAT_AMPLITUDE_HORIZONTAL)
		directionY = 1;

	vY = BAT_FLYING_SPEED_Y * directionY;*/

	//sin one
	posY = 30 * sin(1.5*posX*PI / 180) + tempY;

	Entity::Update(dt);
	posX += dx;
	posY += dy;

#pragma region Past
	//Entity* target;
	////Player is the first unit of vector
	//target = coObjects->at(0);
	//if (!target->IsDeadYet() && !isDead) {
	//	//AI (testing - not neccesary)
	//	D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
	//	//speed nay dc define cho vX (pos += vX * dt) nen khi muon dung cho pos phai nhan voi 1 so tuong duong dt
	//	pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, BAT_FLYING_SPEED * 10);
	//	posX = pos.x;
	//	posY = pos.y;
	//}
	//Entity::Update(dt);

	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	//// turn off collision when die 
	//if (state != BAT_STATE_DIE)
	//	CalcPotentialCollisions(coObjects, coEvents);

	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	posX += dx;
	//	posY += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;

	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	//	// block 
	//	posX += min_tx * dx + nx * 0.6f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	//	posY += min_ty * dy + ny * 0.6f;

	//	if (nx != 0) vX = 0;
	//	if (ny != 0) vY = 0;

	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		if (e->obj->GetType() == EntityType::PLAYER)
	//		{
	//			Player *player = dynamic_cast<Player *>(e->obj);

	//			if (e->ny != 1 && (GetDistance(D3DXVECTOR2(posX, posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= BAT_BBOX_WIDTH/2))
	//			{
	//				if (player->GetState() != PLAYER_STATE_DIE)
	//				{
	//					player->SetState(PLAYER_STATE_DIE);
	//				}
	//			}
	//		}
	//	}
	//}
#pragma endregion
}

void Bat::Render() 
{
	if (isDead)
		return;

	if (direction == 1) {
		sprite->DrawFlipVertical(posX, posY, 255);
	}
	else {
		sprite->Draw(posX, posY, 255);
	}
	RenderBoundingBox();
}

void Bat::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case BAT_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case BAT_STATE_FLYING:
		vX = BAT_FLYING_SPEED_X * direction;
		break;
	}
}

void Bat::GetBoundingBox(float &l, float &t, float &r, float &b) 
{
	//not clean
	if (!isDead) {
		l = posX;
		t = posY;
		r = posX + BAT_BBOX_WIDTH;
		b = posY + BAT_BBOX_HEIGHT;
	}
}
