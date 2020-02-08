#pragma once
#include "GameObject.h"
#include "RapidJsonHelper.h"
#include <vector>

/*
@file StageCreater.h
@brief ステージデータを読み込みステージを生成する
*/
class StageCreater :
	public GameObject
{
public:
	StageCreater();
	~StageCreater();
	/*
	@fn ファイルを開く
	@return 成功か否か
	*/
	bool OpenFile();
	/*
	@fn プレイヤーを生成する
	*/
	class PlayerCharacter* CreatePlayer();
	/*
	@fn ステージを生成する
	*/
	void CreateStage();
	/*
	@fn 衝突を行わない背景を生成する
	*/
	void CreateBackGround();

private:
	/*
	@fn Jsonファイルを読み込みコンテナ型に格納する
	@param _mapDate 格納させたいコンテナへのアドレス
	@param _fileName Jsonファイルアドレス
	@param _layerName Jsonファイル内のレイヤーアドレス
	@return false=失敗
	*/
	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _filename, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& layer, std::string& layerName);
	// ステージデータ
	std::vector<std::vector<int>> mapData;
	//配置するオブジェクトの間隔X
	int sizeX;
	//配置するオブジェクトの間隔Y
	int sizeY;
	//背景データ0
	std::vector<std::vector<int>> backData0;
	//配置するオブジェクトの間隔。サイズ
	float offset;
	//ボスオブジェクトへのポインタ
	class GameObject* bossEnemy;
public://ゲッターセッター
		/*
	@return ボスへのアドレス
	*/
	class GameObject* GetBossEnemy() { return bossEnemy; }
};

