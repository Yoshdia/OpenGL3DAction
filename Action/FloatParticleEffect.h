#pragma once
#include "ParticleEffectBase.h"

/*
@fn FloatParticleEffect.h
@brief 生成すると真上に上昇する
このクラスは必要が無いかもしれない 基底クラスと内容が変わっていない
*/
class FloatParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos 座標
	@param _velocity 移動量
	*/
	FloatParticleEffect(const Vector3& _pos, const Vector3& _velocity);
	~FloatParticleEffect();
private:
	void UpdateParticleObject(float _deltaTime)override;
};

