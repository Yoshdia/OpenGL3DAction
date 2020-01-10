#pragma once
#include "GameObject.h"
#include <string>

class WeaponBase :
	public GameObject
{
public:
	WeaponBase(const Vector3& _pos, const int& _waitCount, const int& _lifeCount, const int& _direction, const Tag& _tag, const Vector3& _colliderSize, const std::string & _meshFileName, const char * _skeletalFileName);
	~WeaponBase();
	void UpdateGameObject(float _deltaTime)override;
protected:
	class RotateComponent* rotateComponent;
	int direction;
	int activeCount;
	virtual void UpdateWeaponGameObject(float _deltaTime) {};
private:
	class ColliderComponent* colliderComponent;
	class SkeletalMeshComponent* skeletalComponent;
	int waitCount;
	int lifeCount;
};

