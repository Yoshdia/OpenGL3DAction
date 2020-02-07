#pragma once
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

class StageCreater :
	public GameObject
{
public:
	StageCreater();
	~StageCreater();

	bool OpenFile();
	class PlayerCharacter* CreatePlayer();
	void CreateStage();
	void CreateBackGround();
	//class GameEndEventSystem* GetEvent() { return endEvent; }
	class GameObject* GetBossEnemy() {return bossEnemy;}
private:
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* filename, const char* layerName);
	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);
	// ステージデータ
	std::vector<std::vector<int>> mapData;
	int sizeX;
	int sizeY;

	std::vector<std::vector<int>> backData0;
	//std::vector<std::vector<int>> backData1;
	float offset;
	class GameObject* bossEnemy;


};

