#pragma once
#include "SceneObjectBase.h"

/*
@file PlaySceneObject.h
@brief プレイシーン
*/
class PlaySceneObject :
	public SceneObjectBase
{
public:
	PlaySceneObject(std::function<void(SceneName)> _SetSceneFunc);
	~PlaySceneObject();

	void UpdateGameObject(float _deltaTime)override;
	void GameObjectInput(const InputState& _keyState)override;
	void PausingUpdateGameObject()override;
private:
	//プレイヤークラス。HPを参照する
	class PlayerCharacter* player;
	//ボスのクラス。オブジェクト状態を参照する
	 GameObject* bossEnemy;
	 //ポーズ画面オブジェクトへのポインタ
	class PauseScreen* pausingScreen;
	/*
	@fn ボスクラスが撃破されたときクリアフラグを建てる
	*/
	void SceneChangeEvents();
	/*
	@fn クリア、ゲームオーバー画面を表示するまでの待機時間を管理し画面を表示する
	*/
	bool EventWordObjectDelay();

	//クリア、ゲームオーバー文字を表示する座標
	static const Vector3 EventWordObjectPos;
	//クリア、ゲームオーバー文字を表示するサイズ
	static const Vector3 EventWordObjectSize;
	//ボスを撃破しクリアしたか
	bool gameClear;
	//プレイヤーの体力がゼロになりゲームオーバーになったか
	bool gameOver;
	//クリア、ゲームオーバー文字を表示してからタイトル画面へ移行するまでの時間
	int endingCount;
	//クリア、ゲームオーバーになってから文字を表示するまでの待機時間
	int endingDelay;
	//クリア、ゲームオーバー文字を表示したか
	bool createdEventWordObject;
	//クリア時に生成するエフェクトの座標
	Vector3 endEffectPos;
};

