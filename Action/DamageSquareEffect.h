#pragma once
#include "ParticleEffectBase.h"

/*
@file DamageSquareEffect.h
@brief 拡大しながら透明度が上がっていくエフェクト
敵の被弾時に使用するためにこの名前にしたが、用途が変わったため改名の必要あり。
*/
class DamageSquareEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos 座標
	*/
	DamageSquareEffect(const Vector3& _pos);
	~DamageSquareEffect();
private:
	/*
	@fn 画像サイズを足し透明度を上げ続ける
	*/
	void UpdateParticleObject(float _deltaTime)override;
	//画像サイズ
	float particleScale;
	//画像の透明度
	float particleAlfa;
};

