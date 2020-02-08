#pragma once
#include "GameObject.h"

class SkeltonObjectChecker;

/*
@file WarpPointSearchEnemy.h
@brief LoiteringEnemyから呼ばれる、ワープ地点を検索するサブアクションクラス
@sa LoiteringEnemyBase.h
*/
class WarpPointSearchEnemy :
	public GameObject
{
public:
	/*
	@param _pos 座標
	*/
	WarpPointSearchEnemy(Vector3 _pos=Vector3(0,0,0));
	~WarpPointSearchEnemy();

	void UpdateGameObject(float _deltaTime)override;

private:
	enum MoveDirection
	{
		right = 1,
		left = -1
	};
	MoveDirection moveDirection;
	bool searchedPoint;
	bool isGround;
	//足元に地面があるか。接地状態を維持する
	SkeltonObjectChecker* footGroundChecker;
	//進行方向に地面があるか。なかった場合そこに停止する
	SkeltonObjectChecker* forwardGroundChecker;
	//進行方向に壁があるか。あった場合そこに停止する
	SkeltonObjectChecker* forwardWallChecker;
public://ゲッターセッター
	/*
	@return 座標の検索が終了したか
	*/
	bool GetEndSearch() { return searchedPoint; };
	/*
	@fn 座標の検索を開始する
	@brief 地面を検索した後に左右どちらかに進むか決定する
	@param _position 検索開始地点
	@param _enemyPosition このオブジェクトを使用しているエネミーの座標
	*/
	void SetFirstPosition(Vector3 _position, Vector3 _enemyPosition);
};

