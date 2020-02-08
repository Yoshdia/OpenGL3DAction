#include "DamageSquareEffect.h"

/*
@file DamageSquareEffect.h
@brief 拡大しながら透明度が上がっていくエフェクト
敵の被弾時に使用するためにこの名前にしたが、用途が変わったため改名の必要あり。
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
@fn 画像サイズを足し透明度を上げ続ける
*/
void DamageSquareEffect::UpdateParticleObject(float _deltaTime)
{
	particleScale += 5.0f;
	particleAlfa -= 0.05f;
	particleComponent->SetScale(particleScale);
	particleComponent->SetAlpha(particleAlfa);
	LifeCountDown();
}
