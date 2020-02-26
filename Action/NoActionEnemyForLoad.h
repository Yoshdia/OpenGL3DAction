#pragma once
#include "EnemyBase.h"

/*
@file NoActionEnemyForLoad.h
@brief 何もアクションを行わないアニメーションを行うだけの敵のクラス。タイトル画面やロード画面に
*/
class NoActionEnemyForLoad :
	public EnemyBase
{
public:
	/*
	@param _pos 座標
	@param _enemyType 敵の種類
	@param _leftDirection 左を向いているか。false=正面を向く
	*/
	NoActionEnemyForLoad(const Vector3& _pos,const EnemyType& _enemyType,const bool& _leftDirection=false);
	~NoActionEnemyForLoad();

	void UpdateGameObject(float _deltaTime)override;
};

