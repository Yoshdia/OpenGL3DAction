#pragma once
#include "GameObject.h"

/*
 @file ThrowWeapon.h
 @brief ���������Ɩ�̂悤�ɔ��ł����v���C���[�̍U��
	*/
class ThrowWeapon :
	public GameObject
{
public:
	/*
	@param _pos ����������W
	@param _direction �������ꂽ�ۂ̃v���C���[�̌���
	*/
	ThrowWeapon(const Vector3& _pos, const int& _direction,const int& _waitTime=0, const Tag& _tag=Tag::PlayerWeaponTag);
	~ThrowWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	void OnTriggerEnter(class ColliderComponent* _pair)override;
	class ColliderComponent* colliderComponent;
	class MeshComponent* meshComponent;
	int waitTime;
	//�������ԁA0�ɂȂ��State��Dead�ɂ���
	int lifeCount;
	int direction;
	Vector3 velocity;
	bool collided;
};

