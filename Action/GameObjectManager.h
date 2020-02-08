                                                                                      #pragma once
#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "GameObject.h"
#include "SceneObjectBase.h"

class GameObject;
struct InputState;

/*
@file GameObjectManager.h
@brief ゲームオブジェクトの更新を行う
*/
class GameObjectManager
{
public:
	/*
	@return 自身のインスタンスを返す
	*/
	static GameObjectManager* GetInstance() { return manager; }
	/*
	@fn インスタンスを生成
	*/
	static void CreateInstance();
	/*
	@fn インスタンスを削除
	*/
	static void DeleteInstance();

	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	void ProcessInput(const InputState& _state);

	/*
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* _object);

	/*
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* _object);

	/*
	@brief 使用したすべてのゲームオブジェクトを解放する
	@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
	*/
	void RemoveAllUsedGameObject();

	GameObject* FindGameObject(Tag _tag);
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* manager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> gameObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;

	//Update中かどうか
	bool updatingGameObject;

	/*
	@fn シーンを変更する この関数をSceneObjectに渡す
	*/
	void SetScene(SceneName _sceneName) { nextScene = _sceneName; }
	//次シーン
	SceneName nextScene;
	//前シーン
	SceneName beforeScene;
	/*
	@fn 次回シーンを参照しながらシーンを変更する
	*/
	void ChangeScene();
};
