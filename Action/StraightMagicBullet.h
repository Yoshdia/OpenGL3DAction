#pragma once
#include "GameObject.h"
class StraightMagicBullet :
	public GameObject
{
public:
	StraightMagicBullet(const Vector3& _shotPosition, const Vector3& _targetPosition, const int& _waitCount);
	~StraightMagicBullet();

	void UpdateGameObject(float _deltaTime)override;
private:
	int waitCount;
	class ColliderComponent* colliderComponent;
	 Vector3 force;
};

