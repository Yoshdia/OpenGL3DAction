#include "HeartParticleEffect.h"



HeartParticleEffect::HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity):
	ParticleEffectBase(_pos,_velocity,30, "Assets/Image/16.png")
{
}


HeartParticleEffect::~HeartParticleEffect()
{
}

void HeartParticleEffect::UpdateParticleObject(float _deltaTime)
{
	LifeCountDown();
	if(velocity.x >= 0.2f||velocity.x<=-0.2f)
	{
		velocity.x /= 1.8f;
	}
	else
	{
		velocity.x = 0;
	}
}
