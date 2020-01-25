#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>

class WeaponBase :
	public GameObject
{
public:
	WeaponBase(const Vector3& _pos, const int& _waitCount, const int& _lifeCount, const int& _direction, const Tag& _tag,const int& _weaponName, const Vector3& _colliderSize,const float& _colorSub, const std::string & _meshFileName, const char * _skeletalFileName);
	~WeaponBase();
	void UpdateGameObject(float _deltaTime)override;
	static int SearchWeaponPower(const int& _objectId);
protected:
	class RotateComponent* rotateComponent;
	int direction;
	int activeCount;
	virtual void UpdateWeaponGameObject(float _deltaTime) {};
	bool doCollision;
private:
	static std::unordered_map<int,int> weapons;
	class ColliderComponent* colliderComponent;
	class SkeletalMeshComponent* skeletalComponent;
	int waitCount;
	int lifeCount;
	float color ;
	float colorSub;
};

