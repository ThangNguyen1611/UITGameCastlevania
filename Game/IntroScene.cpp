#include "IntroScene.h"

#include "SceneManager.h"
#include "PlayScene.h"

IntroScene::IntroScene() : Scene()
{
	keyHandler = new TitleScenceKeyHandler(this);
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());

	screenTexture = Texture2dManager::GetInstance()->GetTexture(EntityType::INTROSCENE);
	screenSprite = new Sprite(screenTexture, MaxFrameRate);

	introSimonTexture = Texture2dManager::GetInstance()->GetTexture(EntityType::INTROSIMON);
	introSimonSprite = new Sprite(introSimonTexture, MaxFrameRate);
	introSimonPosX = SCREEN_WIDTH / 2 - 200;
	introSimonPosY = SCREEN_HEIGHT / 2 + 100;
	introSimonSprite->SelectFrame(SIMON_ANI_IDLE_START);

	timeBeginSimonDelay = 0;
	timeBeginSimonDelayMax = SIMON_BEGIN_WALK_DELAY;

	isDelayPhase1End = false;
	triggerStartPhase2 = false;
	triggerPlay = false;
	isAllowToPlayPhase1 = false;
	isAllowToPlayPhase2 = false;
	isGoingOutside = true;
	isAllowToPlayPhase3 = false;
}

void IntroScene::Load()
{

}

void IntroScene::Unload()
{
	introSimonPosX = 0;
	introSimonPosY = 0;
	timeBeginSimonDelay = 0;
	timeBeginSimonDelayMax = 0;
	isDelayPhase1End = 0;
	isAllowToPlayPhase1 = 0;
	triggerStartPhase2 = 0;
	isAllowToPlayPhase2 = 0;
	isGoingOutside = 0;
	isAllowToPlayPhase3 = 0;
	triggerPlay = 0;

}

void IntroScene::Update(DWORD dt)
{
	timeBeginSimonDelay += dt;
	if (timeBeginSimonDelay < timeBeginSimonDelayMax)	//Delay doan dau
	{
		return;
	}

#pragma region introSimon Phases
	if (isDelayPhase1End && timerEndSimonDelay->IsTimeUp())
	{
		//triggerPlay = true;		//Dung cai nay se khong can phase 2 va 3
		introSimonSprite->SelectFrame(SIMON_ANI_IDLE_START);	//Begin ;)
		triggerStartPhase2 = true;								//Go Phase 2
		timerEndSimonDelay->Reset();
	}

	if (!isAllowToPlayPhase1)		//Chua hoan thanh phase 1
	{
		int currentFrame = introSimonSprite->GetCurrentFrame();
		if (currentFrame < SIMON_ANI_WALKING_BEGIN || currentFrame >= SIMON_ANI_WALKING_END)
			introSimonSprite->SelectFrame(SIMON_ANI_WALKING_BEGIN);

		introSimonSprite->Update(dt);
		//Dung cach update frame update nay se gon hon o titlescreen nhung khong duoc su dung framerate tu. define
		introSimonPosX += SIMON_WALKING_SPEED * dt;	//Chua hoan thanh phase 1 thi di qua phai
	}

	if (introSimonPosX >= SCREEN_WIDTH / 2 && !isDelayPhase1End)	//Cham dich' phase 1
	{
		introSimonSprite->SelectFrame(SIMON_ANI_IDLE_END);
		isAllowToPlayPhase1 = true;		//End phase 1
		timerEndSimonDelay->Start();
		isDelayPhase1End = true;			//Khong vao if nay nua tranh viec Start lai lien tuc
	}

	if (triggerStartPhase2)
	{
		if (!isAllowToPlayPhase2)		//Chua end phase 2
		{
			int currentFrame = introSimonSprite->GetCurrentFrame();
			if (currentFrame < SIMON_ANI_WALKING_BEGIN || currentFrame >= SIMON_ANI_WALKING_END)
				introSimonSprite->SelectFrame(SIMON_ANI_WALKING_BEGIN);

			introSimonSprite->Update(dt);

			if (isGoingOutside)			//Dang di ra ngoai
			{
				introSimonPosX += SIMON_WALKING_SPEED * dt;
			}
		}
		if (introSimonPosX >= SCREEN_WIDTH * 1.5f && !isAllowToPlayPhase3)
		{
			isAllowToPlayPhase3 = true;	//Dat phase 3
			isGoingOutside = false;		//Khong di ra ngoai nua
		}

		if (isAllowToPlayPhase3)		//Phase 3 la di ve
		{
			introSimonPosX += SIMON_WALKING_SPEED * dt * -1;
		}

		if (introSimonPosX <= SCREEN_WIDTH / 2 && isAllowToPlayPhase3)
		{
			isAllowToPlayPhase2 = true;	//Dung update frame
			introSimonSprite->SelectFrame(SIMON_ANI_IDLE_END);	//nen co timer nhung hoi dai` roi
			triggerPlay = true;			//Lets play the game
		}
	}
#pragma endregion

	if (triggerPlay)
	{
		Unload();
		SceneManager::GetInstance()->SetScene(new PlayScene());
	}
}

void IntroScene::Render()
{
	screenSprite->Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (isAllowToPlayPhase3)
		introSimonSprite->Draw(introSimonPosX, SCREEN_HEIGHT / 2 + 150);
	else
		introSimonSprite->DrawFlipVertical(introSimonPosX, SCREEN_HEIGHT / 2 + 150);
}


void IntroScenceKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
		break;
	}
}

void IntroScenceKeyHandler::OnKeyUp(int KeyCode)
{
}

void IntroScenceKeyHandler::KeyState(BYTE *states)
{
}

