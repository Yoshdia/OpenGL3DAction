#pragma once
#include "ParticleEffectBase.h"

class FloatParticleEffect :
	public ParticleEffectBase
{
public:
	FloatParticleEffect(const Vector3& _pos, const Vector3& _velocity);
	~FloatParticleEffect();
private:
	void UpdateParticleObject(float _deltaTime)override;
};

