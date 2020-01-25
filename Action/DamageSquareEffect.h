#pragma once
#include "ParticleEffectBase.h"
class DamageSquareEffect :
	public ParticleEffectBase
{
public:
	DamageSquareEffect(const Vector3& _pos);
	~DamageSquareEffect();

private:
	void UpdateParticleObject(float _deltaTime)override;
	float particleScale;
	float particleAlfa;
};

