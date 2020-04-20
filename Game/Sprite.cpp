#include "Sprite.h"

Sprite::Sprite(Texture2d* TEXTURE, float TIMEPERFRAME)
{
	this->texture = TEXTURE;
	this->timePerFrame = TIMEPERFRAME;
	this->currentFrame = 0;
	totalFrame = texture->GetTotalFrame() - 1;
	spriteHandler = Game::GetInstance()->GetSpriteHandler();
}

Sprite::~Sprite() 
{

}

void Sprite::Update(DWORD dt)
{
	if (totalFrame <= 1)
		return;

	currentTotalTime += dt;	//Check dt and add GameTime

	if (currentTotalTime >= timePerFrame) {
		currentTotalTime = 0;
		currentFrame++;
		if (currentFrame > totalFrame)
			currentFrame = 0;
	}
}

RECT Sprite::GetRectFrame(int CURRENTFRAME)
{
	RECT rec;
	rec.left = CURRENTFRAME % texture->getColumn() * texture->getFrameWidth();	//~ CurrentColumn * FrameWidth
	rec.right = rec.left + texture->getFrameWidth();
	rec.top = CURRENTFRAME / texture->getColumn() * texture->getFrameHeight();	//~ CurrentRow * FrameHeight
	rec.bottom = rec.top + texture->getFrameHeight();

	return rec;
}

void Sprite::Draw(float posX, float posY, int alpha, int R, int G, int B)
{
	RECT rec = GetRectFrame(currentFrame);
	D3DXVECTOR3 pos(floor(posX - Camera::GetInstance()->GetCamPosX()), floor(posY - Camera::GetInstance()->GetCamPosY()), 0);
	//Origin set center (position) is the center of frame, instead of left-top
	D3DXVECTOR3 origin((float)texture->getFrameWidth() / 2, (float)texture->getFrameHeight() / 2, 0);
	spriteHandler->Draw(texture->GetTexture(), &rec, &origin, &pos, D3DCOLOR_ARGB(alpha, R, G, B));
}

void Sprite::DrawFlipVertical(float posX, float posY, int alpha, int R, int G, int B)
{
	RECT rec = GetRectFrame(currentFrame);
	D3DXVECTOR3 pos(floor(posX - Camera::GetInstance()->GetCamPosX()), floor(posY - Camera::GetInstance()->GetCamPosY()), 0);
	D3DXVECTOR3 origin((float)texture->getFrameWidth() / 2, (float)texture->getFrameHeight() / 2, 0);

	D3DXMATRIX oldMatrix, newMatrix;
	D3DXMatrixTransformation2D(&newMatrix, &D3DXVECTOR2(pos.x, pos.y), 0, &D3DXVECTOR2(-1.0, 1.0), NULL, 0, NULL);
	spriteHandler->GetTransform(&oldMatrix);
	spriteHandler->SetTransform(&newMatrix);

	spriteHandler->Draw(texture->GetTexture(), &rec, &origin, &pos, D3DCOLOR_ARGB(alpha, R, G, B));

	spriteHandler->SetTransform(&oldMatrix);
}

void Sprite::Draw1Frame(int idFrame, float posX, float posY, int alpha, int R, int G, int B)
{
	RECT rec = GetRectFrame(idFrame);
	D3DXVECTOR3 pos(floor(posX - Camera::GetInstance()->GetCamPosX()), floor(posY - Camera::GetInstance()->GetCamPosY()), 0);
	//Origin set center (position) is the center of frame, instead of left-top
	D3DXVECTOR3 origin((float)texture->getFrameWidth() / 2, (float)texture->getFrameHeight() / 2, 0);
	spriteHandler->Draw(texture->GetTexture(), &rec, &origin, &pos, D3DCOLOR_ARGB(alpha, R, G, B));
}