#pragma once
#include "GameObject.h"

class SkeltonObjectChecker;

/*
@file WarpPointSearchEnemy.h
@brief LoiteringEnemy����Ă΂��A���[�v�n�_����������T�u�A�N�V�����N���X
@sa LoiteringEnemyBase.h
*/
class WarpPointSearchEnemy :
	public GameObject
{
public:
	/*
	@param _pos ���W
	*/
	WarpPointSearchEnemy(Vector3 _pos=Vector3(0,0,0));
	~WarpPointSearchEnemy();

	void UpdateGameObject(float _deltaTime)override;

private:
	enum MoveDirection
	{
		right = 1,
		left = -1
	};
	MoveDirection moveDirection;
	bool searchedPoint;
	bool isGround;
	//�����ɒn�ʂ����邩�B�ڒn��Ԃ��ێ�����
	SkeltonObjectChecker* footGroundChecker;
	//�i�s�����ɒn�ʂ����邩�B�Ȃ������ꍇ�����ɒ�~����
	SkeltonObjectChecker* forwardGroundChecker;
	//�i�s�����ɕǂ����邩�B�������ꍇ�����ɒ�~����
	SkeltonObjectChecker* forwardWallChecker;
public://�Q�b�^�[�Z�b�^�[
	/*
	@return ���W�̌������I��������
	*/
	bool GetEndSearch() { return searchedPoint; };
	/*
	@fn ���W�̌������J�n����
	@brief �n�ʂ�����������ɍ��E�ǂ��炩�ɐi�ނ����肷��
	@param _position �����J�n�n�_
	@param _enemyPosition ���̃I�u�W�F�N�g���g�p���Ă���G�l�~�[�̍��W
	*/
	void SetFirstPosition(Vector3 _position, Vector3 _enemyPosition);
};

