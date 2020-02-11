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
#include "ShieldEnemy.h"
#include "MageEnemy.h"

StageCreater::StageCreater() :
	GameObject()
{
	offset = 100.0f;
	bossEnemy = nullptr;
}

StageCreater::~StageCreater()
{
	mapData.clear();
}
/*
@fn �t�@�C�����J��
@return �������ۂ�
*/
bool StageCreater::OpenFile()
{
	// �X�e�[�W�f�[�^�ǂݍ��� //DebugArea Stage 
	if (!readTiledJson(mapData, "Assets/Config/Stage.json", "Layer0"))
	{
		printf("mapData�ǂݍ��ݎ��s\n");
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
/*
@fn �v���C���[�𐶐�����
*/
PlayerCharacter* StageCreater::CreatePlayer()
{
	Vector3 pos = Vector3(0, 0, 0);
	for (float iy = 0; iy < sizeY; iy++)
	{
		for (float ix = 0; ix < sizeX; ix++)
		{
			if (mapData[(int)iy][(int)ix] == 1)
			{
				BackGroundObject* back = new BackGroundObject(Vector3(4200, 0, 500), Vector3(5000, 8000, 1), "Back");
				//ParticleObject* back = new ParticleObject(Vector3(4200,-4000, 500), "Assets/Image/BackScreen.png",8000 , 1000);
				pos = Vector3(offset * ix, -offset * iy, 0);

			}
		}
	}
	return new PlayerCharacter(pos);
}
/*
@fn �X�e�[�W�𐶐�����
*/
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
				new GameEndEventSystem(objectPos);
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
				new ComboItemObjectBase(objectPos, ComboItemName::SlashSwordComboItem);
				break;
			case(23):
				new ShieldEnemy(objectPos);
				break;
			}
		}
	}
	SpawnEventSystem* spawn= new SpawnEventSystem(magePos, gatePos, goalPos);
	bossEnemy = spawn->GetMageEnemy();
}
/*
@fn �Փ˂��s��Ȃ��w�i�𐶐�����
*/
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
				case(32):
					new BackGroundObject(objectPos+Vector3(0,0,100), Vector3(50, 50, 50), "blueFloor1");
					break; 
				}
			}
		}
	}
}

/*
@fn Json�t�@�C����ǂݍ��݃R���e�i�^�Ɋi�[����
@param _mapDate �i�[���������R���e�i�ւ̃A�h���X
@param _fileName Json�t�@�C���A�h���X
@param _layerName Json�t�@�C�����̃��C���[�A�h���X
@return false=���s
*/
bool StageCreater::readTiledJson(std::vector<std::vector<int>>& mapData, const char* filename, const char* layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, filename))
	{
		return false;
	}

	// �J����Docment��type �� map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}

	// �J����Document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	// layer���擾
	auto layer = doc["layers"].GetArray();
	int  layerSize = layer.Size();

	// ���C���[������Y�����C���[�̓Y�����l�𒲂ׂ�
	std::string layerNameString(layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer����data�͂���H    
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", layerName);
		return false;
	}

	// ���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ���[�U�[�z��m�� �s�����A������̏��ԂɃT�C�Y�m��
	mapData.resize(height);
	for (auto& mapIter : mapData)
	{
		mapIter.resize(width);
	}

	// ���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[����
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// �Ȃ��� ID�� +1����Ă���̂ŕ␳���� 
			mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

// ���C���[���Ɂ@layerName�̃��C���[���������A���̃C���f�b�N�X�l��Ԃ�
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
