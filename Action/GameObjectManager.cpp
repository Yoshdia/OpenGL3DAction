#include "GameObjectManager.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "MainCameraObject.h"
#include "PlaySceneObject.h"
#include "TitleSceneObject.h"
#include "ResultSceneObject.h"
#include "LoadSceneObject.h"
#include "BackGroundObject.h"

GameObjectManager* GameObjectManager::manager = nullptr;

void GameObjectManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

void GameObjectManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
		manager = nullptr;
	}
}

/**
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{
	//_deltaTime /= 3;
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->Update(_deltaTime);
	}
	updatingGameObject = false;

	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		gameObjects.emplace_back(pending);
	}
	pendingGameObjects.clear();

	if (beforeScene != nextScene)
	{
		beforeScene = nextScene;
		RemoveAllUsedGameObject();
		ChangeScene();
	}
}

void GameObjectManager::ProcessInput(const InputState& _state)
{
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->ProcessInput(_state);
	}
	updatingGameObject = false;
}

/**
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
*/
void GameObjectManager::AddGameObject(GameObject* _object)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{
		gameObjects.emplace_back(_object);
	}
}

/**
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
*/
void GameObjectManager::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(gameObjects.begin(), gameObjects.end(), _object);
	if (iter != gameObjects.end())
	{
		std::iter_swap(iter, gameObjects.end() - 1);
		gameObjects.pop_back();
	}
}

void GameObjectManager::RemoveAllUsedGameObject()
{
	std::vector<GameObject*> reUseObjects;

	while (!gameObjects.empty())
	{
		GameObject* obj = gameObjects.back();
		if (obj->GetReUseGameObject())
		{
			reUseObjects.push_back(obj);
			gameObjects.pop_back();
			continue;
		}
		delete obj;
	}

	gameObjects = reUseObjects;
}

GameObject * GameObjectManager::FindGameObject(Tag _tag)
{
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			return itr;
		}
	}
	return nullptr;
}

std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag _tag)
{
	std::vector<GameObject*> ret;
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			ret.push_back(itr);
		}
	}
	return ret;
}


GameObjectManager::GameObjectManager()
	: updatingGameObject(false),
	nextScene(SceneName::TitleScene),
	beforeScene(SceneName::NoneScene)
{
}


GameObjectManager::~GameObjectManager()
{
	while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}
}

void GameObjectManager::ChangeScene()
{
	std::function<void(SceneName)> func = std::bind(&GameObjectManager::SetScene, this, std::placeholders::_1);
	switch (nextScene)
	{
	case(SceneName::TitleScene):
		new TitleSceneObject(func);
		break;
	case(SceneName::PlayScene):
		new PlaySceneObject(func);
		break;
	case(SceneName::ResultScene):
		new ResultSceneObject(func);
		break;
	case(SceneName::LoadScene):
		new LoadSceneObject(func);
		break;
	}
}
