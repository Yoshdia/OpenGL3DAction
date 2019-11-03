#pragma once
#include "Component.h"
#include "GameObject.h"

/*
 @file JumpPlayerComponent��.h
 @brief �W�����v����
	*/
class JumpPlayerComponent :
	public Component
{
public:
	/*
	@param _jumpPower �W�����v�͂̍ő�l
	*/
	JumpPlayerComponent(GameObject* _owner, int _updateOrder, float _jumpPower);
	~JumpPlayerComponent();

	/*
  @fn ���W�����v�͂�jumpPower�����Z�b�g����
*/
	void Jump(float _deltaTime);

	/*
  @brief�@�W�����v�͂����炵���W���X�V������
*/
	void Update(float _deltaTime)override;


	void JumpEnd() { jumpPower = 0; };
private:
	//���I�ɕω�����W�����v��
	float jumpPower;
	//�W�����v�͂̍ő�l
	float jumpPowerMax;
};

