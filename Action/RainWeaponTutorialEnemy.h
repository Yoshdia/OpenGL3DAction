#pragma once
#include "GameObject.h"

/*
@file RainWeaponTutorialEnemy.h
@brief 一定時間ごとにプレイヤーへダメージを与える攻撃判定を持った武器を生成する
@sa RainEnemyWeapon
*/
class RainWeaponTutorialEnemy :
	public GameObject
{
public:
	/*
@param _pos 座標
*/
	RainWeaponTutorialEnemy(const Vector3& _pos);
	~RainWeaponTutorialEnemy();

	void UpdateGameObject(float _deltaTime)override;
private:
	//武器を生成させる間隔カウント
	int interval;
	//武器を生成させる間隔カウント最大数
	static const int Interval;
};

