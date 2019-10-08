                                                                                      #pragma once
#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "GameObject.h"

class GameObject;
struct InputState;

class GameObjectManager
{
public:
	static GameObjectManager* GetInstance() { return manager; }
	static void CreateInstance();
	static void DeleteInstance();

	/**
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	void UpdateGameObject(float _deltaTime);

	/**
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	void ProcessInput(const InputState& _state);

	/**
	@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
	@param	�ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddGameObject(GameObject* _object);

	/**
	@brief  �Q�[���I�u�W�F�N�g�̍폜
	@param	�폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveGameObject(GameObject* _object);

	GameObject* FindGameObject(Tag _tag);
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* manager;

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	std::vector<GameObject*> gameObjects;
	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> pendingGameObjects;

	//Update�����ǂ���
	bool updatingGameObject;


};
