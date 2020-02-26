#pragma once
#include "EnemyBase.h"

/*
@file NoActionEnemyForLoad.h
@brief �����A�N�V�������s��Ȃ��A�j���[�V�������s�������̓G�̃N���X�B�^�C�g����ʂ⃍�[�h��ʂ�
*/
class NoActionEnemyForLoad :
	public EnemyBase
{
public:
	/*
	@param _pos ���W
	@param _enemyType �G�̎��
	@param _leftDirection ���������Ă��邩�Bfalse=���ʂ�����
	*/
	NoActionEnemyForLoad(const Vector3& _pos,const EnemyType& _enemyType,const bool& _leftDirection=false);
	~NoActionEnemyForLoad();

	void UpdateGameObject(float _deltaTime)override;
};

