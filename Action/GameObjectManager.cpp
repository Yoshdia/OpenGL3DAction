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

/*
@fn �C���X�^���X�𐶐�
*/
void GameObjectManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new GameObjectManager();
		GameObject::CreateMainCamera();
	}
}

/*
@fn �C���X�^���X���폜
*/
void GameObjectManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
		manager = nullptr;
	}
}

/*
@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
*/
void GameObjectManager::UpdateGameObject(float _deltaTime)
{
	updatingGameObject = true;
	//�I�u�W�F�N�g���X�V����
	for (auto gameObject : gameObjects)
	{
		gameObject->Update(_deltaTime);
	}
	updatingGameObject = false;

	//�ҋ@���̃I�u�W�F�N�g���X�V���I�u�W�F�N�g�ɒǉ�
	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		gameObjects.emplace_back(pending);
	}
	pendingGameObjects.clear();

	//�V�[���ɕύX���������
	if (beforeScene != nextScene)
	{
		beforeScene = nextScene;
		RemoveAllUsedGameObject();
		ChangeScene();
	}
}
/*
@brief  �Q�[���I�u�W�F�N�g�̓��͏���
*/
void GameObjectManager::ProcessInput(const InputState& _state)
{
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->ProcessInput(_state);
	}
	updatingGameObject = false;
}

/*
@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
@param	�ǉ�����GameObject�N���X�̃|�C���^
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

/*
@brief  �Q�[���I�u�W�F�N�g�̍폜
@param	�폜����GameObject�N���X�̃|�C���^
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

/*
@brief �g�p�������ׂẴQ�[���I�u�W�F�N�g���������
@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
*/
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

/*
@fn ����V�[�����Q�Ƃ��Ȃ���V�[����ύX����
*/
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
