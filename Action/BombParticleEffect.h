#pragma once
#include "ParticleEffectBase.h"
class BombParticleEffect :
	public ParticleEffectBase
{
public:
	BombParticleEffect(const Vector3& _pos, const Vector3& _velocity,const bool& _collisionForGround);
	~BombParticleEffect();
private:
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	void UpdateParticleObject(float _deltaTime)override;
	bool collisionForGround;
};

