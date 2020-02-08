#pragma once
#include "GameObject.h"

/*
@file EventSystem.h
@brief �C�x���g�V�X�e���N���X���ĕ�炷 �����𖞂����ƍX�V���I������
*/
class EventSystem :
	public GameObject
{
public:
	/*
	@param _pos ���W
	*/
	EventSystem(const Vector3& _pos);
	~EventSystem();

	void UpdateGameObject(float _deltaTime)override;
protected:
	//�����𖞂�������
	bool trigger;
private:
	/*
	@fn �h���N���X�̍X�V�֐�
	*/
	virtual void UpdateEventObject() {};
};

