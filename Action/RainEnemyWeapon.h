#pragma once
#include "GameObject.h"

/*
@file RainEnemyWeapon.h
@brief プレイヤーへダメージを与える落下するオブジェクト
@sa RainWeaponTutorialEnemy
*/
class RainEnemyWeapon :
	public GameObject
{
public:
	/*
	@param _pos 座標
	*/
	RainEnemyWeapon(const Vector3& _pos);
	~RainEnemyWeapon();

	void UpdateGameObject(float _deltaTime)override;
private:
	//活動時間
	int activeCount;
};

