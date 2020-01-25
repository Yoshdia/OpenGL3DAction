#include "DamageSquareEffect.h"



DamageSquareEffect::DamageSquareEffect(const Vector3 & _pos) :
	ParticleEffectBase(_pos, Vector3(0, 0, 0), 30, "Assets/Image/damageSquare.png"),
	particleScale(0.1f),
	particleAlfa(1.0f)
{
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
}

DamageSquareEffect::~DamageSquareEffect()
{
}

void DamageSquareEffect::UpdateParticleObject(float _deltaTime)
{
	particleScale += 5.0f;
	particleAlfa -= 0.05f;
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
	LifeCountDown();
}
