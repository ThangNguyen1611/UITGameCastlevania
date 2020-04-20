#pragma once

#include <unordered_map>
#include "define.h"
#include "Texture2d.h"

class Texture2dManager
{
	static Texture2dManager* __instance;
	std::unordered_map<EntityType, Texture2d*> Textures;

public:
	Texture2dManager();
	~Texture2dManager();

	static Texture2dManager* GetInstance();
	Texture2d* GetTexture(EntityType tag) { return Textures[tag]; }
	void AddTexture(EntityType tag, Texture2d* texture) { Textures[tag] = texture; }
	void LoadContent();
};

