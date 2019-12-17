#pragma once
#include "GameObject.h"


class EnemyWeapon :
	public GameObject
{
public:
	EnemyWeapon();
	EnemyWeapon(Vector3 _pos,Vector3 _size,int lifeCount,int _waitTime);
	~EnemyWeapon();

	void UpdateGameObject(float _deltaTime)override;
private:
	int lifeCount;
	int waitTime;

	class MeshComponent* meshComponent  ;
	class ColliderComponent* collisionComp;
};

