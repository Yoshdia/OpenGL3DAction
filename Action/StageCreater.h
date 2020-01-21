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
	class GameEndEventSystem* GetEvent() {return endEvent;}
private:
	bool readTiledJson(std::vector<std::vector<int>>& mapData, const char* filename, const char* layerName);
	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);
	// ステージデータ
	std::vector<std::vector<int>> mapData;
	int sizeX;
	int sizeY;
	int offset;
	class GameEndEventSystem* endEvent;
};

