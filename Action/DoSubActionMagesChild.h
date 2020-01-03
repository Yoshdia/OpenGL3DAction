#pragma once
#include "GameObject.h"

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
};

