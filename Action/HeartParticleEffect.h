#pragma once
#include "ParticleEffectBase.h"

/*
 @file HeartParticleEffect.h
 @brief ハートの画像を上昇させるエフェクト
*/
class HeartParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos 座標
	@param _velocity 移動量
	@param _broken 壊れたハートか。これを参照し生成する画像を変更する
	*/
	HeartParticleEffect(const Vector3& _pos, const Vector3& _velocity,const bool& broken=false);
	~HeartParticleEffect();
private:
	/*
	@fn velocity.xを一定値以下になるまで減少させ続ける
	*/
	void UpdateParticleObject(float _deltaTime)override;
};

