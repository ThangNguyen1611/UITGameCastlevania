#include "Gate.h"

Gate::Gate(float posX, float posY, int switchId)
{
	this->texture = Texture2dManager::GetInstance()->GetTexture(EntityType::GATE);
	this->sprite = new Sprite(texture, MaxFrameRate);
	tag = EntityType::GATE;
	this->posX = posX;
	this->posY = posY;
	gateSwitchSceneId = switchId;
}

Gate::~Gate(){}

void Gate::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	sprite->SelectFrame(GATE_ANI_BASIC_FORM);
}

void Gate::Render()
{
	RenderBoundingBox();

	if (gateSwitchSceneId == 2 || gateSwitchSceneId == 4)	//Gate tai stage 1 3 khong ve~
		return;

	sprite->Draw(posX, posY);
}

void Gate::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = posX;
	t = posY;
	r = posX + GATE_BBOX_WIDTH;
	b = posY + GATE_BBOX_HEIGHT;
}
