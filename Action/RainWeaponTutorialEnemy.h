#pragma once
#include "GameObject.h"

/*
@file RainWeaponTutorialEnemy.h
@brief ��莞�Ԃ��ƂɃv���C���[�փ_���[�W��^����U�����������������𐶐�����
@sa RainEnemyWeapon
*/
class RainWeaponTutorialEnemy :
	public GameObject
{
public:
	/*
@param _pos ���W
*/
	RainWeaponTutorialEnemy(const Vector3& _pos);
	~RainWeaponTutorialEnemy();

	void UpdateGameObject(float _deltaTime)override;
private:
	//����𐶐�������Ԋu�J�E���g
	int interval;
	//����𐶐�������Ԋu�J�E���g�ő吔
	static const int Interval;
};

