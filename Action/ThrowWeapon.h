#pragma once
#include "WeaponBase.h"

/*
 @file ThrowWeapon.h
 @brief 生成されると矢のように飛んでいくプレイヤーの攻撃
	*/
class ThrowWeapon :
	public WeaponBase
{
public:
	/*
	@param _pos 生成する座標
	@param _direction 生成された際のプレイヤーの向き
	*/
	ThrowWeapon(const Vector3& _pos, const float& _direction,const int& _waitTime, const Tag& _tag=Tag::PlayerWeaponTag);
	~ThrowWeapon();
private:
	void UpdateWeaponGameObject(float _deltaTime);
	void OnTriggerStay(ColliderComponent* _collider)override;
	Vector3 velocity;
	bool collided;
	bool slow;
};

