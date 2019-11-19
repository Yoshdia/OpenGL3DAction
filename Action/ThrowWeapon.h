#pragma once
#include "GameObject.h"

/*
 @file ThrowWeapon.h
 @brief ���������Ɣ��ł����v���C���[�̍U��
	*/
class ThrowWeapon :
	public GameObject
{
public:
	/*
	@param _pos ����������W
*/
	ThrowWeapon(const Vector3& _pos);
	~ThrowWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	class MeshComponent* meshComponent;
	//�������ԁA0�ɂȂ��State��Dead�ɂ���
	int lifeCount;
};

