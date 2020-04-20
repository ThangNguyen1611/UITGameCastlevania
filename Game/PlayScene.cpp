#include "PlayScene.h"

PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	LoadBaseObjects();
	ChooseMap(STAGE_1);
}

void PlayScene::LoadBaseObjects()
{
	if (player == NULL)
	{
		player = new Player(100, 280);
		//listObjects.push_back(player);
		DebugOut(L"[INFO] Simon object created! \n");
	}
	gameUI = new UI(player->GetHealth(), 16);
	gameTime = GameTime::GetInstance();		//That ra khong can 2 buoc nay vi ca 2 deu thiet ke Singleton
	camera = Camera::GetInstance();
	map = new Map();
}

void PlayScene::ChooseMap(int whatMap)	
//Muc dich chinh ham nay la chon ra sceneFilePath can thiet, co the kh dung ham nay ma tao if else o ham Load cung duoc
{
	switch (whatMap)
	{
	case STAGE_1:
	{
		idStage = STAGE_1;
		Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
		map->LoadMap(MAPSTAGE1);
		player->ReceiveCurrentStage(idStage);

		sceneFilePath = ToLPCWSTR("Resources/Scene/scene1.txt");
		Load();
		break;
	}
	case STAGE_2_1:
	{
		idStage = STAGE_2_1;
		Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
		map->LoadMap(MAPSTAGE2_1);
		player->ReceiveCurrentStage(idStage);

		gameTime->ResetGameTime();	//Reset lai gameTime

		easterEgg_Stage2_1 = 0;
		////Zombie Logic
		//counterZombie = 0;
		//isTimeToSpawnZombie = true;		//vua vao spawn luon
		//triggerSpawnZombie = false;
		////Bat Logic
		//isTimeToSpawnBat = true;
		//triggerSpawnBat = true;

		sceneFilePath = ToLPCWSTR("Resources/Scene/scene2_1.txt");
		Load();
		break;
	}
	case STAGE_2_2:
	{
		idStage = STAGE_2_2;
		Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
		map->LoadMap(MAPSTAGE2_2);
		player->ReceiveCurrentStage(idStage);

		gameTime->ResetGameTime();	//Reset lai gameTime

		easterEgg_Stage2_2 = 0;

		sceneFilePath = ToLPCWSTR("Resources/Scene/scene2_2.txt");
		Load();
		break;
	}
	case STAGE_3_1:
	{
		idStage = STAGE_3_1;
		Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
		map->LoadMap(MAPSTAGE3_1);
		player->ReceiveCurrentStage(idStage);

		gameTime->ResetGameTime();	//Reset lai gameTime

		sceneFilePath = ToLPCWSTR("Resources/Scene/scene3_1.txt");
		Load();
		break;
	}
	case STAGE_3_2:
	{
		idStage = STAGE_3_2;
		Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
		map->LoadMap(MAPSTAGE3_2);
		player->ReceiveCurrentStage(idStage);

		gameTime->ResetGameTime();	//Reset lai gameTime

		sceneFilePath = ToLPCWSTR("Resources/Scene/scene3_2.txt");
		Load();
		break;
	}
	default:
		break;
	}
}

Effect* PlayScene::CreateEffect(EntityType createrType, EntityType effectType, float posX, float posY)
{
	if (effectType == EntityType::HITEFFECT)
		return new Hit(posX - HIT_EFFECT_CUSTOMIZED_POS, posY - HIT_EFFECT_CUSTOMIZED_POS);
	else if (effectType == EntityType::FIREEFFECT)
		return new Fire(posX, posY);
	else if (effectType == EntityType::ADDSCOREEFFECT)
		return new Score(posX, posY, createrType);
	else
		return new Hit(posX - HIT_EFFECT_CUSTOMIZED_POS, posY - HIT_EFFECT_CUSTOMIZED_POS);
}

Item* PlayScene::DropItem(EntityType createrType, float posX, float posY, int idCreater)
{
	int bagrandom = rand() % 100;
	if (createrType == EntityType::NONE)		//special case
	{
		if(idStage == STAGE_2_1)
			return new Crown(posX, posY);
		else
			if (idStage == STAGE_2_2)
				return new ExtraShot(posX, posY, 2);
	}

	if (createrType == EntityType::TORCH)
	{
		if (idCreater == 1)
		{
			return new BigHeart(posX, posY);
		}
		else 
			if (idCreater == 2) 
			{
				return new UpgradeMorningStar(posX, posY);
			}
			else 
				if (idCreater == 3) 
				{
					return new ItemDagger(posX, posY);
				}
				else
				{
					int random = rand() % 1000;
					if (random <= 200)
						return new SmallHeart(posX, posY);
					else if (200 < random && random <= 400)
						return new BigHeart(posX, posY);
					else if (400 < random && random <= 600)
						return new YummiChickenLeg(posX, posY);
					else if (600 < random && random <= 800)
						return new UpgradeMorningStar(posX, posY);
					else
					{
						if (bagrandom <= 33)
							return new MoneyBags(posX, posY, EntityType::MONEYBAGRED);
						else if (33 < bagrandom && bagrandom <= 66)
							return new MoneyBags(posX, posY, EntityType::MONEYBAGWHITE);
						else
							return new MoneyBags(posX, posY, EntityType::MONEYBAGBLUE);
					}
				}
	}
	else
		if (createrType == EntityType::CANDLE)
		{
			if (idCreater == 1)
			{
				return new SmallHeart(posX, posY);
			}
			else
			{
				int random = rand() % 1000;
				if (random <= 200)
					return new SmallHeart(posX, posY);
				else if (200 < random && random <= 400)
					return new BigHeart(posX, posY);
				else if (400 < random && random <= 600)
					return new YummiChickenLeg(posX, posY);
				else if (600 < random && random <= 800)
					return new UpgradeMorningStar(posX, posY);
				else
				{
					if (bagrandom <= 33)
						return new MoneyBags(posX, posY, EntityType::MONEYBAGRED);
					else if (33 < bagrandom && bagrandom <= 66)
						return new MoneyBags(posX, posY, EntityType::MONEYBAGWHITE);
					else
						return new MoneyBags(posX, posY, EntityType::MONEYBAGBLUE);
				}
			}
		}
	else 
		if (createrType == EntityType::ZOMBIE || createrType == EntityType::KNIGHT || createrType == EntityType::DARKENBAT)
	{
		int random = rand() % 1000;
		if (random <= 200)
			return new SmallHeart(posX, posY);
		else if (200 < random && random <= 400)
			return new BigHeart(posX, posY);
		else if (400 < random && random <= 600)
			return new YummiChickenLeg(posX, posY);
		else if (600 < random && random <= 800)
			return new UpgradeMorningStar(posX, posY);
		else
		{
			if (bagrandom <= 33)
				return new MoneyBags(posX, posY, EntityType::MONEYBAGRED);
			else if (33 < bagrandom && bagrandom <= 66)
				return new MoneyBags(posX, posY, EntityType::MONEYBAGWHITE);
			else
				return new MoneyBags(posX, posY, EntityType::MONEYBAGBLUE);
		}
	}
	else
		if (createrType == EntityType::BAT)
		{
			return new ItemDagger(posX, posY);
		}
		else
			return new BigHeart(posX, posY);
}

void PlayScene::WeaponInteractObj(UINT i, bool isMainWeapon)
{
	//Co 1 phuong an de delay DropItem la trigger Start timer o day, o update thi lien tuc check timer de push
	//Van de la timer co hoat dong dung khong khi giet nhieu target 1 luc ?	//Phuong an la dat timer trong class cua item
	switch (listObjects[i]->GetType())
	{
	case EntityType::BAT:
		if (listObjects[i]->GetHealth() == 1)	//Hit nay se chet 
		{
			player->AddScore(500);
			listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		break;
	case EntityType::DARKENBAT:
		if (listObjects[i]->GetHealth() == 1)	//Hit nay se chet 
		{
			player->AddScore(500);
			listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		break;
	case EntityType::ZOMBIE:
		if (listObjects[i]->GetHealth() == 1)	//Hit nay se chet 
		{
			player->AddScore(100);
			listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		
		counterZombie--;
		if (counterZombie == 0)
		{
			spawningZombieTimer->Start();
			triggerSpawnZombie = true;
			isTimeToSpawnZombie = false;
		}
		break;
	case EntityType::KNIGHT:
		if (listObjects[i]->GetHealth() == 1)	//Hit nay se chet 
		{
			player->AddScore(200);
			listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		break;
	case EntityType::TORCH:
	{
		Torch* torch = dynamic_cast<Torch*>(listObjects[i]);	//Extension cua DropItem
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), torch->GetIdTorch()));
		break;
	}
	case EntityType::CANDLE:
	{
		Candle* candle = dynamic_cast<Candle*>(listObjects[i]);	//Extension cua DropItem
		listObjects[i]->AddHealth(-1);
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), candle->GetIdCandle()));
		break;
	}
	case EntityType::BREAKABLEBRICK:
	{
		if (isMainWeapon)
		{
			if (idStage == STAGE_2_1)
			{
				easterEgg_Stage2_1++;
			}
			else 
				if (idStage == STAGE_2_2)
				{
					easterEgg_Stage2_2++;
				}
			listObjects[i]->AddHealth(-1);
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		break;
	}
	default:
		break;
	}
}

void PlayScene::SetSubWeaponDone(UINT i)
{
	if (listObjects[i]->GetType() == EntityType::BAT ||
		listObjects[i]->GetType() == EntityType::ZOMBIE ||
		listObjects[i]->GetType() == EntityType::TORCH ||
		listObjects[i]->GetType() == EntityType::DARKENBAT ||
		listObjects[i]->GetType() == EntityType::KNIGHT ||
		listObjects[i]->GetType() == EntityType::BREAKABLEBRICK)
	{
		switch (player->GetPlayerSupWeaponType())
		{
		case EntityType::DAGGER:
			player->GetPlayerSupWeapon()->SetIsDone(true);
		default:
			break;
		}
	}
}

void PlayScene::WeaponCollision()
{
	if (!player->GetPlayerMainWeapon()->GetIsDone() || player->GetPlayerSupWeapon() != NULL)	//Hoac dang dung vu khi chinh, hoac dang co vu khi phu
	{
		for (UINT i = 0; i < listObjects.size(); i++)
		{
			if (player->GetPlayerMainWeapon()->IsCollidingObject(listObjects[i]))	//Main weapon va cham voi obj
			{
				WeaponInteractObj(i, true);
				//old
				/*switch (listObjects[i]->GetType())
				{
				case EntityType::BAT:
					listObjects[i]->AddHealth(-1);
					player->AddScore(500);
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					break;
				case EntityType::ZOMBIE:
					listObjects[i]->AddHealth(-1);
					player->AddScore(100);
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					counterZombie--;
					if (counterZombie == 0)
					{
						spawningZombieTimer->Start();
						triggerSpawnZombie = true;
						isTimeToSpawnZombie = false;
					}
					break;
				case EntityType::TORCH:
					listObjects[i]->AddHealth(-1);
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				default:
					break;
				}*/
			}
			else
				if (player->GetPlayerSupWeapon() != NULL //Dong nay de dam bao dong ben duoi khong bi break
					&& player->GetPlayerSupWeapon()->IsCollidingObject(listObjects[i]))
				{
					WeaponInteractObj(i, false);
					SetSubWeaponDone(i);
				}
		}
	}
}

void PlayScene::PlayerCollideItem()
{
	for (UINT i = 0; i < listItems.size(); i++)
	{
		if (!listItems[i]->GetIsDone())
		{
			if (player->IsCollidingObject(listItems[i]))
			{
				switch (listItems[i]->GetType())
				{
				case EntityType::MONEYBAGRED:
					//Vi cai nay ma phai dem CollideItem tu Player ra ngoai -.-
					//Ton biet bao nhieu suc
					player->AddScore(100);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGRED, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::MONEYBAGWHITE:
					player->AddScore(400);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGWHITE, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::MONEYBAGBLUE:
					player->AddScore(700);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGBLUE, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::SMALLHEART:
					player->AddMana(1);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::BIGHEART:
					player->AddMana(5);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::YUMMICHICKENLEG:
					player->AddScore(1000);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::CROWN:
					player->AddScore(10000);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::ITEMEXTRASHOT:
					//Xet type extra
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::UPGRADEMORNINGSTAR:
				{
					//nang cap ms
					//Dung yen simon 1 ty
					MorningStar* morningStarWeapon = dynamic_cast<MorningStar*>(player->GetPlayerMainWeapon());
					player->UpgradingMorningStar();
					morningStarWeapon->UpLevel();
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMDAGGER:
				{
					player->SetPlayerSupWeaponType(EntityType::DAGGER);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMBOOMERANG:
				{
					player->SetPlayerSupWeaponType(EntityType::BOOMERANG);
					listItems[i]->SetIsDone(true);
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

bool PlayScene::PlayerPassingStage(float DistanceXWant, int directionGo)
{
	if (directionGo == 1)	//cua o ben phai
	{
		if (player->GetPosX() < DistanceXWant)
		{
			player->SetDirection(directionGo);
			player->SetState(PLAYER_STATE_PASSING_STAGE);
			return false;
		}
	}
	else
		if (directionGo == -1)	//cua o ben trai
		{
			if (player->GetPosX() > DistanceXWant)
			{
				player->SetDirection(directionGo);
				player->SetState(PLAYER_STATE_PASSING_STAGE);
				return false;
			}
		}
	return true;
}

void PlayScene::PlayerGotGate()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::GATE)
		{
			if (player->IsCollidingObject(listObjects[i]))
			{
				if (idStage == STAGE_1)
				{
					if (PlayerPassingStage(listObjects[i]->GetPosX() + 20.0f, 1))
					{
						Unload();
						ChooseMap(STAGE_2_1);
						player->SetPosition(50, 365);
						player->SetVx(0);
						player->SetVy(0);
						player->SetState(PLAYER_STATE_IDLE);
					}
				}
				else if (idStage == STAGE_2_2)
				{
					if (PlayerPassingStage(listObjects[i]->GetPosX() - 10.0f, -1))
					{
						Unload();
						ChooseMap(STAGE_3_1);
						player->SetPosition(1440, 350);
						player->SetVx(0);
						player->SetVy(0);
						player->SetState(PLAYER_STATE_IDLE);
					}
				}
			}
		}
	}
}

bool PlayScene::PlayerGotStairs()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::STAIRS)
		{
			Stairs* stair = dynamic_cast<Stairs*>(listObjects[i]);
			if (player->IsCollidingObject(listObjects[i]))
			{
				player->SetDirection(stair->GetDirection());
				/*if (listObjects[i]->GetDirection() == 1)
				{

				}
				else
				{

				}*/
				/*if (player->GetDirection() == 1)
				{
					DebugOut(L"Up Stair \n");
					player->SetState(PLAYER_STATE_GOING_UP_STAIRS);
				}
				else
				{
					DebugOut(L"Down Stair \n");
					player->SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
				}*/
				return true;
			}
			/*else
			{
				player->SetOnStair(false);
			}*/
		}
	}
	return false;
}

void PlayScene::PlayerFailDown()
{
	if (idStage == STAGE_2_2)
	{
		if (player->GetPosX() <= 544)
		{
			if (player->GetPosY() >= 441)
			{
				player->AddHealth(-player->GetHealth());
			}
		}
	}
	else
		if (idStage == STAGE_3_2)
		{
			if (player->GetPosY() >= 441)
			{
				player->AddHealth(-player->GetHealth());
			}
		}
}

void PlayScene::EasterEggEvent()
{
	if (idStage == STAGE_2_1)
	{
		if (easterEgg_Stage2_1 == 2)
		{
			listItems.push_back(DropItem(EntityType::NONE, 240.0f, 441.0f));
			easterEgg_Stage2_1 = 0;
		}
	}
	else
		if (idStage == STAGE_2_2)
		{
			if (easterEgg_Stage2_2 == 1)
			{
				listItems.push_back(DropItem(EntityType::NONE, 720.0f, 233.0f));
				easterEgg_Stage2_2 = 0;
			}
		}
}

void PlayScene::CheckObjAlive()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		LPGAMEENTITY coO = listObjects[i];
		if (coO->GetHealth() > 0)	//Xet object con song	//object health < 0 con xu li o trong zombie.cpp update
			switch (coO->GetType())
			{
			case EntityType::BAT:
				if (coO->GetPosX() < 0 || coO->GetPosX() > SCREEN_WIDTH * 2)
				{
					coO->SetState(BAT_STATE_DIE);
				}
				break;
			case EntityType::ZOMBIE:
				if (coO->GetPosY() > SCREEN_HEIGHT + 200)
				{
					coO->SetState(ZOMBIE_STATE_DIE);
					counterZombie--;
					if (counterZombie == 0)
					{
						spawningZombieTimer->Start();
						triggerSpawnZombie = true;
						isTimeToSpawnZombie = false;	//De khong vao if voi
					}
				}
				break;
			default:
				break;
			}
	}
}

void PlayScene::Update(DWORD dt)
{
#pragma region Scan Game Periodically
	//Nen co 1 lan quet toan bo object cua game moi 100 hoac 1000 lan update
	/*if (!isScanned && scanningGameTimer->IsTimeUp())
	{
		isScanned = true;
		if (isScanned)
		{
			ScanEntitiesPeriodically(listObjects);
			isScanned = false;
		}
		scanningGameTimer->Reset();
		scanningGameTimer->Start();
	}*/
#pragma endregion
#pragma region Checking alive object is in screen
	CheckObjAlive();
#pragma endregion
#pragma region Spawning Zombie Logic
#pragma region Failed Operation Spawning Each Zombie
	////auto if = true neu counter chua len 3 do spawningTimer kh thay doi
	//if (isTimeToSpawnZombie) {
	//	if (counterZombie <= 3 && spawningZombieTimer->IsTimeUp())
	//	{
	//		if (delaySpawningZombieTimer->IsTimeUp())	//IsTimeUp nay vao duoc do co Start o dieu kien duoi
	//		{
	//			listObjects.push_back(new Zombie(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT - 150, -1));
	//			counterZombie++;

	//			delaySpawningZombieTimer->Reset();		//Reset va start su dung nhu 1 vong lap (ap dung ham Update)
	//			delaySpawningZombieTimer->Start();
	//		}
	//		if (counterZombie == 3)	//counter len 3 thay doi spawningTimer de thoat khoi if thu nhat
	//		{
	//			spawningZombieTimer->Reset();
	//			counterZombie = 0;
	//			isTimeToSpawnZombie = false;
	//		}
	//	}
	//	if (triggerSpawnZombie)	//STAR: Dat Dieu kien Start sau counter++
	//	{
	//		spawningZombieTimer->Start();
	//		//start dau tien cua delay de co the vao IsTimeUp cua no
	//		delaySpawningZombieTimer->Start();
	//		triggerSpawnZombie = false;	//Bien trigger giup cho spawning zombie chi thuc hien khi dang co 0 hoac 3 zombie
	//	}
	//}
#pragma endregion
	if (isTimeToSpawnZombie)
	{
		if (delaySpawningZombieTimer->IsTimeUp()) 
		{
			if (counterZombie < 3)
			{
				listObjects.push_back(new Zombie(SCREEN_WIDTH / 2 + 400, SCREEN_HEIGHT - 150, -1));
				counterZombie++;
				if (counterZombie >= 3)
				{
					isTimeToSpawnZombie = false;	//out ra khoi if nay
					triggerSpawnZombie = false;		//out ra ca if sau
				}
				delaySpawningZombieTimer->Start();
			}
		}
	}
	else
	{
		if (triggerSpawnZombie)
		{
			if(spawningZombieTimer->IsTimeUp())
			{
				isTimeToSpawnZombie = true;
			}
		}
	}
#pragma endregion
#pragma region Spawning Bat Logic
	if (isTimeToSpawnBat) {
		if (spawningBatTimer->IsTimeUp())
		{
			listObjects.push_back(new Bat(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT - 150, 1));
			spawningBatTimer->Reset(SPAWNING_BAT_DELAY + (rand() % 3000));
			triggerSpawnBat = true;	//Dung 1 cho thi se spawn bat mai mai, cho den khi di den khu vuc ma trigger o do = false
		}
		if (triggerSpawnBat)
		{
			spawningBatTimer->Start();
			triggerSpawnBat = false;
		}
	}
#pragma endregion
#pragma region Objects Updates
	vector<LPGAMEENTITY> coObjects;
	for (int i = 0; i < listObjects.size(); i++)
	{
		coObjects.push_back(listObjects[i]);
	}
	player->Update(dt, &coObjects);
	for (int i = 0; i < listObjects.size(); i++)
	{
		listObjects[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < listEffects.size(); i++)
	{
		listEffects[i]->Update(dt);
	}
	for (int i = 0; i < listItems.size(); i++)
	{
		listItems[i]->Update(dt, &listObjects);
	}
#pragma endregion
#pragma region Camera
	float cx, cy;
	player->ReceivePos(cx, cy);
	//1250
	if (idStage == STAGE_1 && player->GetPosX() >= STAGE_1_MAX_WIDTH)
	{
		cx -= SCREEN_WIDTH / 2 - (STAGE_1_MAX_WIDTH - player->GetPosX());
	}
	else
		if (idStage == STAGE_2_1 && player->GetPosX() >= STAGE_2_1_MAX_WIDTH)
		{
			cx -= SCREEN_WIDTH / 2 - (STAGE_2_1_MAX_WIDTH - player->GetPosX());
		}
		else
			if (idStage == STAGE_2_2 && player->GetPosX() >= STAGE_2_2_MAX_WIDTH)
			{
				cx -= SCREEN_WIDTH / 2 - (STAGE_2_2_MAX_WIDTH - player->GetPosX());
			}
			else
				if (idStage == STAGE_3_1 && player->GetPosX() >= STAGE_3_1_MAX_WIDTH)
				{
					cx -= SCREEN_WIDTH / 2 - (STAGE_3_1_MAX_WIDTH - player->GetPosX());
				}
				else
					if (idStage == STAGE_3_2 && player->GetPosX() >= STAGE_3_2_MAX_WIDTH)
					{
						cx -= SCREEN_WIDTH / 2 - (STAGE_3_2_MAX_WIDTH - player->GetPosX());
					}
	else
	{
		if (player->GetPosX() < SCREEN_WIDTH / 2)
			//cx -= SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 2 - player->GetPosX());
			cx = 0;
		else
			cx -= SCREEN_WIDTH / 2;
	}
	cy -= SCREEN_HEIGHT / 2;

	camera->SetCamPos(cx, 0.0f);//cy khi muon camera move theo y player //castlevania chua can
#pragma endregion

	WeaponCollision();
	PlayerCollideItem();
	PlayerGotGate(); 
	//PlayerGotStairs();
	PlayerFailDown();
	EasterEggEvent();

	gameTime->Update(dt);
	gameUI->Update(cx + 260, 35, player->GetHealth(), 16);	//move posX follow camera

}

void PlayScene::Render()
{
	map->Draw();
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Render();
	for (int i = 0; i < listEffects.size(); i++)
		listEffects[i]->Render();
	for (int i = 0; i < listItems.size(); i++)
		listItems[i]->Render();
	player->Render();
	gameUI->Render(idStage, SCENEGAME_GAMETIMEMAX - gameTime->GetTime(), player);
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Player* simon = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObj = ((PlayScene*)scence)->listObjects;

	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
	case DIK_1:	//test auto
		simon->KnownTargetMovement(simon->GetPosX() + 200, simon->GetPosY(), PLAYER_WALKING_SPEED, 0);
		break;
	case DIK_2:	//test jump stage
		playScene->Unload();
		playScene->ChooseMap(playScene->idStage + 1);
		if (playScene->idStage == STAGE_2_1)
		{
			simon->SetPosition(400, 150);
		}
		else
			if (playScene->idStage == STAGE_2_2)
			{
				simon->SetPosition(800, 150);
			}
			else 
				if (playScene->idStage == STAGE_3_1)
				{
					simon->SetPosition(1440, 350);
				}
				else 
					if (playScene->idStage == STAGE_3_2)
					{
						simon->SetPosition(304, 200);
					}

		simon->SetVx(0);
		simon->SetVy(0);
		simon->SetState(PLAYER_STATE_IDLE);
		break;
	case DIK_R:
		for (int i = 0; i < listObj.size(); i++)
		{
			if (listObj[i]->GetBBARGB() == 0)
				listObj[i]->SetBBARGB(200);
			else
				listObj[i]->SetBBARGB(0);
		}

		if (simon->GetBBARGB() == 0)
			simon->SetBBARGB(200);
		else
			simon->SetBBARGB(0);

		if (simon->GetPlayerMainWeapon()->GetBBARGB() == 0)
			simon->GetPlayerMainWeapon()->SetBBARGB(200);
		else
			simon->GetPlayerMainWeapon()->SetBBARGB(0);
		break;
	case DIK_C:
		if (simon->IsDeadYet() || simon->IsAttacking() || simon->IsSitting() || simon->IsHurting() || simon->IsUpgrading() || simon->IsPassingStage() || simon->IsProcessingAuto())
			return;
		simon->SetState(PLAYER_STATE_JUMP);
		break;
	case DIK_X:
		if (simon->IsDeadYet() || simon->IsHurting() || simon->IsUpgrading() || Game::GetInstance()->IsKeyDown(DIK_UP) || simon->IsPassingStage() || simon->IsProcessingAuto())	//Up + X khong Whip duoc nua
			return;
		simon->SetState(PLAYER_STATE_ATTACK);
		break;
	}
}

void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void PlayScenceKeyHandler::KeyState(BYTE *states)
{
	Player* simon = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;

	if (simon->IsDeadYet() ||  simon->IsHurting() || simon->IsUpgrading() || simon->IsPassingStage()) 
	{
		return;
	}
	
	//if (!simon->IsOnStairs())
	//{
		if (Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_X) && !simon->IsAttacking())
		{
			if (simon->GetPlayerSupWeaponType() != EntityType::NONE)	//Neu chua nhat duoc vu khi phu thi khong attack
			{
				simon->SetState(PLAYER_STATE_SUPWEAPON_ATTACK);
			}
		}
		else
			if (!simon->IsJumping() && !simon->IsAttacking())	//tranh simon nhay len stair
			{
				if (Game::GetInstance()->IsKeyDown(DIK_UP))
				{
					if (simon->IsOnStairs())
					{
						for (UINT i = 0; i < listObjects.size(); i++)
						{
							if (listObjects[i]->GetType() == EntityType::STAIRS)
							{
								if (simon->IsCollidingObject(listObjects[i]))
								{
									DebugOut(L"Reach Stair \n");
									simon->SetDirection(listObjects[i]->GetDirection());
									DebugOut(L"Up Stair \n");
									simon->SetState(PLAYER_STATE_GOING_UP_STAIRS);
									simon->KnownTargetMovement(listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), PLAYER_ON_STAIRS_SPEED_X, PLAYER_ON_STAIRS_SPEED_Y, listObjects[i]->GetDirection(), 1);
								}
							}
						}
					}
					else
					{
						for (UINT i = 0; i < listObjects.size(); i++)
						{
							if (listObjects[i]->GetType() == EntityType::STAIRS)
							{
								if (simon->IsCollidingObject(listObjects[i]))
								{
									DebugOut(L"Reach Stair \n");
									DebugOut(L"Up Stair \n");
									simon->SetState(PLAYER_STATE_GOING_UP_STAIRS);
								}
							}
						}
					}
				}
				else
					if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
					{
						if (simon->IsOnStairs())
						{
							for (UINT i = 0; i < listObjects.size(); i++)
							{
								if (listObjects[i]->GetType() == EntityType::STAIRS)
								{
									if (simon->IsCollidingObject(listObjects[i]))
									{
										DebugOut(L"Reach Stair \n");
										simon->SetDirection(-listObjects[i]->GetDirection());
										DebugOut(L"Down Stair \n");
										simon->SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
										simon->KnownTargetMovement(listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), PLAYER_ON_STAIRS_SPEED_X, PLAYER_ON_STAIRS_SPEED_Y, -listObjects[i]->GetDirection(), -1);
									}
								}
							}
						}
						else
						{
							for (UINT i = 0; i < listObjects.size(); i++)
							{
								if (listObjects[i]->GetType() == EntityType::STAIRS)
								{
									if (simon->IsCollidingObject(listObjects[i]))
									{
										DebugOut(L"Reach Stair \n");
										DebugOut(L"Down Stair \n");
										simon->SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
									}
								}
							}
						}
					}
					//else
					//{
					//	//DebugOut(L"Not Stair \n");
					//	simon->SetState(PLAYER_STATE_IDLE);
					//}
			}

		if (simon->IsOnStairs() || simon->IsProcessingAuto() || simon->IsAttacking() || simon->IsJumping() )
			return;

		if (Game::GetInstance()->IsKeyDown(DIK_DOWN)) {
			simon->SetState(PLAYER_STATE_SITTING);
			if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
				simon->SetDirection(1);
			else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
				simon->SetDirection(-1);
			return;				//Important return //Dont change state while sitting
		}
		else simon->SetState(PLAYER_STATE_IDLE);

		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->SetState(PLAYER_STATE_WALKING_RIGHT);
		else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->SetState(PLAYER_STATE_WALKING_LEFT);
		else simon->SetState(PLAYER_STATE_IDLE);
	//}
	/*else
	{
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		{
			if (simon->GetDirectionY() == 1)
			{
				simon->SetDirection(1);
				simon->SetState(PLAYER_STATE_GOING_UP_STAIRS);
			}
			else
				if(simon->GetDirectionY() == -1)
			{
					simon->SetDirection(1);
					simon->SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
			}
		}
		else
		{
			if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			{
				if (simon->GetDirectionY() == 1)
				{
					simon->SetDirection(-1);
					simon->SetState(PLAYER_STATE_GOING_UP_STAIRS);
				}
				else
					if (simon->GetDirectionY() == -1)
					{
						simon->SetDirection(-1);
						simon->SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
					}
			}
			else
			{
				simon->SetState(PLAYER_STATE_IDLE);
			}
		}
	}*/
}

/*
	Parse a line in section [OBJECTS]
*/
void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	switch (object_type)
	{
	case OBJECT_TYPE_CANDLE:
	{
		int extras = atoi(tokens[3].c_str());
		listObjects.push_back(new Candle(x, y, extras));
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		int extras = atoi(tokens[3].c_str());
		listObjects.push_back(new Brick(x, y, extras));
		break;
	}
	case OBJECT_TYPE_TORCH:
	{
		int extras = atoi(tokens[3].c_str());
		listObjects.push_back(new Torch(x, y, extras));
		break; 
	}
	case OBJECT_TYPE_GATE:
	{
		int extras = atoi(tokens[3].c_str());
		listObjects.push_back(new Gate(x, y, extras));
		break;
	}
	case OBJECT_TYPE_STAIRS:
	{
		int extras1 = atoi(tokens[3].c_str());
		int extras2 = atoi(tokens[4].c_str());
		listObjects.push_back(new Stairs(x, y, extras1, extras2));
		break;
	}
	case OBJECT_TYPE_DARKENBAT:
	{
		//player tao truoc nen kh sao
		int extras1 = atoi(tokens[3].c_str());
		listObjects.push_back(new DarkenBat(x, y, extras1, player));
		break;
	}
	case OBJECT_TYPE_KNIGHT:
	{
		int extras1 = atoi(tokens[3].c_str());
		int extras2 = atoi(tokens[4].c_str());
		listObjects.push_back(new Knight(x, y, extras1, extras2));
		break;
	}
	case OBJECT_TYPE_BREAKABLEBRICK:
	{
		int extras1 = atoi(tokens[3].c_str());
		listObjects.push_back(new BreakableBrick(x, y, extras1));
		break;
	}
	case OBJECT_TYPE_MOVING_PLATFORM:
	{
		listObjects.push_back(new MovingPlatform(x, y));
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
}

void PlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_OBJECTS:
			_ParseSection_OBJECTS(line);
			break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Unload()
{
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	for (int i = 0; i < listEffects.size(); i++)
		delete listEffects[i];
	for (int i = 0; i < listItems.size(); i++)
		delete listItems[i];
	listObjects.clear();
	listEffects.clear();
	listItems.clear();
}
