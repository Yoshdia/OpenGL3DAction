#pragma once
#include "GameObject.h"

/*
 @file ThrowWeapon.h
 @brief 生成されると飛んでいくプレイヤーの攻撃
	*/
class ThrowWeapon :
	public GameObject
{
public:
	/*
	@param _pos 生成する座標
*/
	ThrowWeapon(const Vector3& _pos);
	~ThrowWeapon();
	void UpdateGameObject(float _deltaTime)override;
private:
	class MeshComponent* meshComponent;
	//生存時間、0になるとStateをDeadにする
	int lifeCount;
};

