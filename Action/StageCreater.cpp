#include "StageCreater.h"
#include "DebugBox.h"
#include "PlayerCharacter.h"
#include "SpawnEventSystem.h"
#include "CandleStick.h"
#include "MeleeEnemy.h"
#include "TankEnemy.h"
#include "RangeEnemy.h"
#include "ComboItemObjectBase.h"
#include "GameEndEventSystem.h"
#include "RainWeaponTutorialEnemy.h"
#include "ParticleObject.h"
#include "Ground.h"
#include "BackGroundObject.h"

StageCreater::StageCreater() :
	GameObject()
{
	offset = 100.0f;
	endEvent = nullptr;
}

StageCreater::~StageCreater()
{
	mapData.clear();
}

bool StageCreater::OpenFile()
{
	// ステージデータ読み込み //DebugArea Stage DebugArea
	if (!readTiledJson(mapData, "Assets/Config/Stage.json", "Layer0"))
	{
		printf("mapData読み込み失敗\n");
		return true;
	}
	sizeX = mapData[0].size();
	sizeY = mapData.size();
	if (!readTiledJson(backData0, "Assets/Config/Stage.json", "BackGround0"))
	{
		printf("do'nt have Layer/BackGround0\n");
	}
	//if (!readTiledJson(backData1, "Assets/Config/Stage.json", "BackGround1"))
	//{
	//	printf("do'nt have Layer/BackGround0\n");
	//}
	return false;
}

PlayerCharacter* StageCreater::CreatePlayer()
{
	Vector3 pos = Vector3(0, 0, 0);
	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			if (mapData[(int)iy][(int)ix] == 1)
			{
				//ParticleObject* back = new ParticleObject(Vector3(4200,-4000, 500), "Assets/Image/BackScreen.png",8000 , 1000);
				pos = Vector3(offset * ix, -offset * iy, 0);

			}
		}
	}
	return new PlayerCharacter(pos);
}

void StageCreater::CreateStage()
{
	Vector3 magePos = Vector3();
	Vector3 gatePos = Vector3();
	Vector3 goalPos = Vector3();
	int gateC = 0;

	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			const unsigned int name = mapData[(int)iy][(int)ix];
			Vector3 objectPos = Vector3(offset * ix, -offset * iy, 0);
			Vector3 objectSize = Vector3(50, 50, 100);
			switch (name)
			{
			case(1):
				break;
			case(2):
				new Ground(objectPos+  Vector3(0, 0, 50), objectSize);
				break;
			case(3):
				new Ground(objectPos + Vector3(0, 45, 50), Vector3(50, 5, 100), Tag::ThinGroundFloor);
				break;
			case(4):
				new CandleStick(objectPos);
				break;
			case(5):
				magePos = objectPos;
				break;
			case(6):
				if (gateC == 0)
				{
					gatePos = objectPos;
				}
				else
				{
					goalPos = objectPos;
				}
				gateC++;
				break;
			case(7):
				endEvent = new GameEndEventSystem(objectPos);
				break;
			case(8):
				new RainWeaponTutorialEnemy(objectPos);
				break;
			case(9):
				new MeleeEnemy(objectPos);
				break;
			case(10):
				new RangeEnemy(objectPos);
				break;
			case(11):
				new TankEnemy(objectPos);
				break;
			case(12):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Move.png", 160.0f);
				break;
			case(13):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Jump.png", 160.0f);
				break;
			case(14):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/DoubleJump.png", 160.0f);
				break;
			case(15):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Pass.png", 160.0f);
				break;
			case(16):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Rolling.png", 160.0f);
				break;
			case(17):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Attack.png", 160.0f);
				break;
			case(18):
				new ParticleObject(objectPos, "Assets/Image/Tutorial/Heal.png", 160.0f);
				break;
			case(19):
				new ComboItemObjectBase(objectPos, ComboItemName::RotateComboItem);
				break;
			case(20):
				new ComboItemObjectBase(objectPos, ComboItemName::ThrowComboItem);
				break;
			case(21):
				new ComboItemObjectBase(objectPos, ComboItemName::HammerComboItem);
				break;
			case(22):
				break;
			}
		}
	}
	new SpawnEventSystem(magePos, gatePos, goalPos);

}

void StageCreater::CreateBackGround()
{
	if (!backData0.empty())
	{
		for (float iy = 0; iy < sizeY; iy++)
		{
			for (float ix = 0; ix < sizeX; ix++)
			{
				const unsigned int name = backData0[(int)iy][(int)ix];
				Vector3 objectPos = Vector3(offset * ix, -offset * iy, 0);
				switch (name)
				{
				case(31):
					new BackGroundObject(objectPos, Vector3(50, 50, 50), "blueFloor1");
					break; 
				}
			}
		}
	}
	//if (!backData1.empty())
	//{

	//	for (float iy = 0; iy < sizeY; iy++)
	//	{
	//		for (float ix = 0; ix < sizeX; ix++)
	//		{
	//			const unsigned int name = backData1[(int)iy][(int)ix];
	//			Vector3 objectPos = Vector3(offset * ix, -offset * iy, offset);
	//			if (name != 0)
	//			{
	//				int i = 0;
	//			}
	//			switch (name)
	//			{
	//			case(32):
	//				new BackGroundObject(objectPos, Vector3(50, 50, 50), "BlackFloor");
	//				break;
	//			}
	//		}
	//	}
	//}
}

// Tiled形式のJsonファイルを読み込む
bool StageCreater::readTiledJson(std::vector<std::vector<int>>& mapData, const char* filename, const char* layerName)
{
	//RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!openJsonFile(doc, filename))
	{
		return false;
	}

	// 開いたDocmentのtype は mapか？
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}

	// 開いたDocumentにlayerはあるか？
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	// layer数取得
	auto layer = doc["layers"].GetArray();
	int  layerSize = layer.Size();

	// レイヤー名から該当レイヤーの添え字値を調べる
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer内にdataはある？    
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", layerName);
		return false;
	}

	// レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ユーザー配列確保 行方向、列方向の順番にサイズ確保
	mapData.resize(height);
	for (auto& mapIter : mapData)
	{
		mapIter.resize(width);
	}

	// ユーザー配列（2次元）にデータをコピーする
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// なぜか IDが +1ずれているので補正する 
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

// レイヤー内に　layerNameのレイヤーを検索し、そのインデックス値を返す
int StageCreater::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName)
{
	int  layerSize = layer.Size();

	int i;
	std::string layerNameString(layerName);
	for (i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}
