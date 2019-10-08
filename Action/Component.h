#pragma once

#include <cstdint>

class GameObject;

class Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
	Component(GameObject* _owner,int _updateOrder = 100);
	virtual ~Component();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime);

	/**
	@brief	���͏���
	@param	InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/**
	@brief	Transform�̃��[���h�ϊ�
	*/
	virtual void OnUpdateWorldTransform() {}

	/**
	@brief	UpdateOrder���擾����
	@return UpdateOrder�i���l���������قǑ����X�V�����j
	*/
	int GetUpdateOder() { return updateOrder; }

    GameObject* GetOwner() { return owner; };


protected:

	//�A�^�b�`���Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	GameObject* owner;			
	// �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	int updateOrder;

};

