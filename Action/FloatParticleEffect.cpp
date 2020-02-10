#include "FloatParticleEffect.h"

/*
@param _pos ���W
@param _velocity �ړ���
*/
FloatParticleEffect::FloatParticleEffect(const Vector3& _pos, const Vector3& _velocity):
	ParticleEffectBase(_pos,_velocity,30,"Assets/Image/Effect/SummonedFlash.png")
{
	particleComponent->SetScale(30);
}


FloatParticleEffect::~FloatParticleEffect()
{
}

void FloatParticleEffect::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(position + velocity);
}
