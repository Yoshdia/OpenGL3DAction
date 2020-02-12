#pragma once
#include "ParticleEffectBase.h"

/*
@file BombParticleEffect.h
@brief 地面との衝突判定を行い、反射するような挙動を撮取るエフェクト
*/
class BombParticleEffect :
	public ParticleEffectBase
{
public:
	/*
	@param _pos 座標
	@param _velocity 移動量
	*/
	BombParticleEffect(const Vector3& _pos, const Vector3& _velocity);
	~BombParticleEffect();
	/*
	@fn 画面が静止しているときに残り続けないようカウントダウンを続ける
	*/
	void PausingUpdateGameObject()override;
private:
	/*
	@fn 地面と衝突したときにvelocity.yを反転させvelocity.xを減少させる
	*/
	void OnTriggerEnter(ColliderComponent* colliderPair) override;
	/*
	@fn 重力を反映させる
	*/
	void UpdateParticleObject(float _deltaTime)override;
	ColliderComponent* col;
};

