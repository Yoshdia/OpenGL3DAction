#pragma once
#include "ParticleEffectBase.h"
class HeartParticleEffect :
	public ParticleEffectBase
{
public:
	HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity,const bool& broken=false);
	~HeartParticleEffect();
private:
	void UpdateParticleObject(float _deltaTime)override;
};

