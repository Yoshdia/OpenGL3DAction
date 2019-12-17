#pragma once
#include "GameObject.h"

class ParticleEffect :
	public GameObject
{
public:
	ParticleEffect(Vector3 _pos,Vector3 _velocity=Vector3(0,0,0),bool _collionForGround=true);
	~ParticleEffect();
	void UpdateGameObject(float _deltaTime)override;
	void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)override;
private:
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	Vector3 velocity;
	bool collisionForGround;
	int direction;
	int lifeCount;
	bool isCollision;
};

