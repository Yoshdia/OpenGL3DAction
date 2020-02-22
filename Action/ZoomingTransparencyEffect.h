#pragma once
#include "ParticleEffectBase.h"

/*
@file ZoomingTransparencyEffect.h
@brief 拡大しながら透明度が上がっていくエフェクト
*/
class ZoomingTransparencyEffect :
	public ParticleEffectBase
{
public:
	/*
@param _pos 座標
*/
	ZoomingTransparencyEffect(const Vector3& _pos);
	~ZoomingTransparencyEffect();
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

