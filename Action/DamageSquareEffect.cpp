#include "DamageSquareEffect.h"

/*
@file DamageSquareEffect.h
@brief �g�債�Ȃ��瓧���x���オ���Ă����G�t�F�N�g
�G�̔�e���Ɏg�p���邽�߂ɂ��̖��O�ɂ������A�p�r���ς�������߉����̕K�v����B
*/
DamageSquareEffect::DamageSquareEffect(const Vector3 & _pos) :
	ParticleEffectBase(_pos, Vector3(0, 0, 0), 30, "Assets/Image/Effect/damageSquare.png"),
	particleScale(0.1f),
	particleAlfa(1.0f)
{
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
}

DamageSquareEffect::~DamageSquareEffect()
{
}

/*
@fn �摜�T�C�Y�𑫂������x���グ������
*/
void DamageSquareEffect::UpdateParticleObject(float _deltaTime)
{
	particleScale += 5.0f;
	particleAlfa -= 0.05f;
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
	LifeCountDown();
}
