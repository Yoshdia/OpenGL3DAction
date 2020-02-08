#pragma once
#include "GameObject.h"

/*
@file EnemyWeapon.h
@brief エネミーの攻撃。基本的にアニメーションと共に生成し攻撃判定にする。ヒットボックスを想像
*/
class EnemyWeapon :
	public GameObject
{
public:
	/*
	@param _pos 座標
	@param _size サイズ
	@param _lifeCount 判定時間
	@param _waitTime 攻撃発生まで待機時間
	*/
	EnemyWeapon(Vector3 _pos,Vector3 _size,int _lifeCount,int _waitTime);
	~EnemyWeapon();

	/*
	@fn 生存時間を減少させ続けゼロになった時このオブジェクトの更新を止める
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	//生存時間
	int lifeCount;
	//待機時間
	int waitTime;
	//デバッグ用。ヒットボックスの確認に
	class MeshComponent* meshComponent;
	//衝突判定を行うクラス
	class ColliderComponent* collisionComp;
};

