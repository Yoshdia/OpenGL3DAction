#pragma once
#include "GameObject.h"

/*
@file RainEnemyWeapon.h
@brief �v���C���[�փ_���[�W��^���闎������I�u�W�F�N�g
@sa RainWeaponTutorialEnemy
*/
class RainEnemyWeapon :
	public GameObject
{
public:
	/*
	@param _pos ���W
	*/
	RainEnemyWeapon(const Vector3& _pos);
	~RainEnemyWeapon();

	void UpdateGameObject(float _deltaTime)override;
private:
	//��������
	int activeCount;
};

