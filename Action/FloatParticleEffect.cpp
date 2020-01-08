#include "FloatParticleEffect.h"



FloatParticleEffect::FloatParticleEffect(const Vector3& _pos, const Vector3& _velocity):
	ParticleEffectBase(_pos,_velocity,30,"Assets/Image/16.png")
{
	particleComponent->SetScale(20);
}


FloatParticleEffect::~FloatParticleEffect()
{
}

void FloatParticleEffect::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
	SetPosition(position + velocity);
}
