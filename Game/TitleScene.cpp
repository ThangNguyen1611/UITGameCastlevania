#include "TitleScene.h"
#include "SceneManager.h"
#include "IntroScene.h"

TitleScene::TitleScene() : Scene()
{
	keyHandler = new TitleScenceKeyHandler(this);
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_titlescene.txt");
	LoadBaseTextures();

	titleSceneSpr = CSprites::GetInstance()->Get(TITLESCREEN_SPRITES);
	batAniSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_TITLEBAT);
	startAniSet = CAnimationSets::GetInstance()->Get(ANIMATION_SET_STARTTEXT);

	isAllowToStart = false;
}

void TitleScene::LoadSceneObjects()
{

}

void TitleScene::Unload()
{

}

void TitleScene::Update(DWORD dt)
{
	if (batAniSet->at(0)->GetCurrentFrame() == BAT_ENDFRAME)
	{
		isAllowToStart = true;
	}
}

void TitleScene::Render()
{
	titleSceneSpr->Draw(-1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	batAniSet->at(0)->Render(-1, SCREEN_WIDTH / 2 + 185, SCREEN_HEIGHT / 2 + 40);
	if (isAllowToStart)
		startAniSet->at(0)->Render(-1, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50);
}

void TitleScenceKeyHandler::OnKeyDown(int KeyCode)
{
	bool canStart = ((TitleScene*)scence)->isAllowToStart;

	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
	case DIK_I:
		if (canStart)
		{
			((TitleScene*)scence)->Unload();
			SceneManager::GetInstance()->SetScene(new IntroScene());
		}

		break;
	}
}

void TitleScenceKeyHandler::OnKeyUp(int KeyCode)
{
}

void TitleScenceKeyHandler::KeyState(BYTE *states)
{
}

void TitleScene::_ParseSection_TEXTURES(string line)
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

void TitleScene::_ParseSection_SPRITES(string line)
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

void TitleScene::_ParseSection_ANIMATIONS(string line)
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

void TitleScene::_ParseSection_ANIMATION_SETS(string line)
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


void TitleScene::LoadBaseTextures()
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