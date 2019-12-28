#pragma once
#include "GameObject.h"

/*
 @file ThrowWeapon.h
 @brief 生成されると矢のように飛んでいくプレイヤーの攻撃
	*/
class ThrowWeapon :
	public GameObject
{
public:
	/*
	@param _pos 生成する座標
	@param _direction 生成された際のプレイヤーの向き
	*/
	ThrowWeapon(const Vector3& _pos, const int& _direction, const Tag& _tag=Tag::PlayerWeaponTag);
	~ThrowWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	void OnTriggerEnter(class ColliderComponent* _pair)override;
	class MeshComponent* meshComponent;
	//生存時間、0になるとStateをDeadにする
	int lifeCount;
	int direction;
	Vector3 velocity;
	bool collided;
};

