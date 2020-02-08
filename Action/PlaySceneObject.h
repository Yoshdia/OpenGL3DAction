#pragma once
#include "SceneObjectBase.h"

/*
@file PlaySceneObject.h
@brief �v���C�V�[��
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
	//�v���C���[�N���X�BHP���Q�Ƃ���
	class PlayerCharacter* player;
	//�{�X�̃N���X�B�I�u�W�F�N�g��Ԃ��Q�Ƃ���
	 GameObject* bossEnemy;
	 //�|�[�Y��ʃI�u�W�F�N�g�ւ̃|�C���^
	class PauseScreen* pausingScreen;
	/*
	@fn �{�X�N���X�����j���ꂽ�Ƃ��N���A�t���O�����Ă�
	*/
	void SceneChangeEvents();
	/*
	@fn �N���A�A�Q�[���I�[�o�[��ʂ�\������܂ł̑ҋ@���Ԃ��Ǘ�����ʂ�\������
	*/
	bool EventWordObjectDelay();

	//�N���A�A�Q�[���I�[�o�[������\��������W
	static const Vector3 EventWordObjectPos;
	//�N���A�A�Q�[���I�[�o�[������\������T�C�Y
	static const Vector3 EventWordObjectSize;
	//�{�X�����j���N���A������
	bool gameClear;
	//�v���C���[�̗̑͂��[���ɂȂ�Q�[���I�[�o�[�ɂȂ�����
	bool gameOver;
	//�N���A�A�Q�[���I�[�o�[������\�����Ă���^�C�g����ʂֈڍs����܂ł̎���
	int endingCount;
	//�N���A�A�Q�[���I�[�o�[�ɂȂ��Ă��當����\������܂ł̑ҋ@����
	int endingDelay;
	//�N���A�A�Q�[���I�[�o�[������\��������
	bool createdEventWordObject;
	//�N���A���ɐ�������G�t�F�N�g�̍��W
	Vector3 endEffectPos;
};

