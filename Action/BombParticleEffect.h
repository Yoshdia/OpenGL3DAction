#pragma once
#include "ParticleEffectBase.h"
class BombParticleEffect :
	public ParticleEffectBase
{
public:
	BombParticleEffect(const Vector3& _pos, const Vector3& _velocity,const bool& _collisionForGround);
	~BombParticleEffect();
	void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)override;
private:
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	void UpdateParticleObject(float _deltaTime)override;
	bool collisionForGround;
	bool isCollision;
};

