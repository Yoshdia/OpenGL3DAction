#include "ZoomingTransparencyEffect.h"

ZoomingTransparencyEffect::ZoomingTransparencyEffect(const Vector3& _pos) :
	ParticleEffectBase(_pos, Vector3(0, 0, 0), 30, "Assets/Image/Effect/damageSquare.png"),
	particleScale(0.2f),
	particleAlfa(1.0f)
{
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
}

ZoomingTransparencyEffect::~ZoomingTransparencyEffect()
{
}
/*
@fn �摜�T�C�Y�𑫂������x���グ������
*/
void ZoomingTransparencyEffect::UpdateParticleObject(float _deltaTime)
{
	particleScale += 5.0f;
	particleAlfa -= 0.05f;
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
	LifeCountDown();
}