#pragma once
#include "GameObject.h"
#include "EnemyBase.h"

/*
 @file DoSubActionMagesChild.h
 @brief 親オブジェクトの移動を親クラスからの要件に合わせ行う MageEnemyクラスにて使用
 @detail 地面へ接触するまで落下、一定の高さまで浮上、左右の壁に当たるまで左右移動がある
	*/
class DoSubActionMagesChild :
	public GameObject
{
public:
	/*
	@param _owner 親となるオブジェクトクラス
	*/
	DoSubActionMagesChild(GameObject* _owner);
	~DoSubActionMagesChild();

	/*
	@fn どの行動を行うか判断し、行う
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn このクラス内の定数分の高さまで浮上する
	*/
	void StartFloating();
	/*
	@fn サブクラスが地面を検知するまで落下する
	@sa SkeltonObjectChecker.h
	*/
	void StartDroppingDown();

	/*
	@return 浮上、落下のどちらも終了している状態(true=終了
	*/
	bool EndFloatDrop() { return !(floating || droppingDown); }
	/*
	@fn 水平を指定する変数をもとに移動する。壁に当たると変数を反転する
	*/
	void MoveHorizontal();
	/*
	@fn 垂直を指定する変数をもとに移動する。一定間隔ごとに変数を反転する
	*/
	void HuwaHuwa();
private:
	//親オブジェクトへのポインタ
	GameObject* owner;
	//浮上する高さ
	static const float FloatHeight;
	//浮上の目標となる高さ FloatHeight+親オブジェクトの高さ
	float targetHeight;
	//浮上速度
	static const float FloatSpeed;
	//浮上の命令が親オブジェクトから来ていたか droppingDownと同時に建つことはない
	bool floating;
	
	//地面を検知するクラス
	class SkeltonObjectChecker* footChcker;
	//落下の命令が親オブジェクトから来ていたか floatingと同時に建つことはない
	bool droppingDown;
	//落下速度
	static const float DroppingSpeed;

	//移動方向
	EnemyMoveDirection moveDirection;
	//右方向の壁を探知する
	class SkeltonObjectChecker* rightWallChecker;
	//左方向の壁を探知する
	class SkeltonObjectChecker* leftWallChecker;
	//縦の移動方向
	EnemyMoveDirection verticalMoveDirection;
	//縦方向の移動方向反転カウント
	int verticalInversionCount;
};

