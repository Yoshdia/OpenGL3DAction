#include "FloatParticleEffect.h"

/*
@param _pos À•W
@param _velocity ˆÚ“®—Ê
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
