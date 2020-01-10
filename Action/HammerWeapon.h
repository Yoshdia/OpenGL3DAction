#pragma once
#include "GameObject.h"

class HammerWeapon :
	public GameObject
{
public:
	HammerWeapon(const Vector3& _pos,const int& number, const int& _direction,const int& _lifeCount, const int& _waitTime = 0);
	~HammerWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	ColliderComponent* colliderComponent;
	class SkeletalMeshComponent* skeletal;
	class RotateComponent* rotate;
	int waitTime;
	//¶‘¶ŠÔA0‚É‚È‚é‚ÆState‚ğDead‚É‚·‚é
	int lifeCount;
	int rotateSpeed;
};

