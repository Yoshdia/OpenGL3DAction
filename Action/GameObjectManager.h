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
@brief �Q�[���I�u�W�F�N�g�̍X�V���s��
*/
class GameObjectManager
{
public:
	/*
	@return ���g�̃C���X�^���X��Ԃ�
	*/
	static GameObjectManager* GetInstance() { return manager; }
	/*
	@fn �C���X�^���X�𐶐�
	*/
	static void CreateInstance();
	/*
	@fn �C���X�^���X���폜
	*/
	static void DeleteInstance();

	/*
	@brief  �Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g����
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̓��͏���
	*/
	void ProcessInput(const InputState& _state);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
	@param	�ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddGameObject(GameObject* _object);

	/*
	@brief  �Q�[���I�u�W�F�N�g�̍폜
	@param	�폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveGameObject(GameObject* _object);

	/*
	@brief �g�p�������ׂẴQ�[���I�u�W�F�N�g���������
	@detail �V�[���J�ڂ̍ۂɎg�p�����BGameObject���̍ė��p�t���O�������Ă���I�u�W�F�N�g�͉�����Ȃ�
	*/
	void RemoveAllUsedGameObject();

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

	/*
	@fn �V�[����ύX���� ���̊֐���SceneObject�ɓn��
	*/
	void SetScene(SceneName _sceneName) { nextScene = _sceneName; }
	//���V�[��
	SceneName nextScene;
	//�O�V�[��
	SceneName beforeScene;
	/*
	@fn ����V�[�����Q�Ƃ��Ȃ���V�[����ύX����
	*/
	void ChangeScene();
};
