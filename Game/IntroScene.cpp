#include "IntroScene.h"

#include "SceneManager.h"
#include "PlayScene.h"

IntroScene::IntroScene() : Scene()
{
	keyHandler = new TitleScenceKeyHandler(this);
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_introscene.txt");
	LoadTextures();

	introSceneSpr = CSprites::GetInstance()->Get(268);
	simonAniSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_INTROSIMON);
	introSimonPosX = SCREEN_WIDTH / 2 - 200;
	introSimonPosY = SCREEN_HEIGHT / 2 + 100;
	simonState = SIMON_STATE_IDLE;

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
	simonState = 0;
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
		simonState = SIMON_STATE_WALKING;	//Begin ;)
		triggerStartPhase2 = true;								//Go Phase 2
		timerEndSimonDelay->Reset();
	}

	if (!isAllowToPlayPhase1)		//Chua hoan thanh phase 1
	{
		simonState = SIMON_STATE_WALKING;
		introSimonPosX += SIMON_WALKING_SPEED * dt;	//Chua hoan thanh phase 1 thi di qua phai
	}

	if (introSimonPosX >= SCREEN_WIDTH / 2 && !isDelayPhase1End)	//Cham dich' phase 1
	{
		simonState = SIMON_STATE_IDLE_END;
		isAllowToPlayPhase1 = true;		//End phase 1
		timerEndSimonDelay->Start();
		isDelayPhase1End = true;			//Khong vao if nay nua tranh viec Start lai lien tuc
	}

	if (triggerStartPhase2)
	{
		if (!isAllowToPlayPhase2)		//Chua end phase 2
		{
			simonState = SIMON_STATE_WALKING;
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
			simonState = SIMON_STATE_IDLE_END;	//nen co timer nhung hoi dai` roi
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
	introSceneSpr->Draw(-1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (isAllowToPlayPhase3)
		simonAniSet->at(simonState)->Render(-1, introSimonPosX, SCREEN_HEIGHT / 2 + 150);
	else
		simonAniSet->at(simonState)->Render(1, introSimonPosX, SCREEN_HEIGHT / 2 + 150);
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


void IntroScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void IntroScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void IntroScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void IntroScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}


void IntroScene::LoadTextures()
{
	DebugOut(L"[INFO] Start loading TEXTURES resources from : %s \n", texturesFilePath);

	ifstream f;
	f.open(texturesFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading TEXTURES resources %s\n", texturesFilePath);
}
