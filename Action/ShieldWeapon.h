#pragma once
#include "GameObject.h"
#include <functional>

/*
 @file ShieldWeapon.h
 @brief プレイヤーから生成される盾
	*/
class ShieldWeapon :
	public GameObject
{
public:
	/*
	param _AddGuardingObjectIdFunc このオブジェクトと接触したオブジェクトIDを渡す先の関数ポインタ
	*/
	ShieldWeapon(std::function<void(const int&)> _AddGuardingObjectIdFunc);
	~ShieldWeapon();
	/*
	@brief 生成された際の演出、アクティブ時間の管理
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn 生成
	@brief 各カウントや座標をリセットする
	@param 生成する座標 この座標から少し高い座標に生成されこの座標に落下する
	*/
	void CreateShield(const Vector3& _pos);
private:
	/*
	@brief コンストラクタから受け取った関数に衝突したオブジェクトのIDを渡す
	*/
	void OnTriggerStay(ColliderComponent* _colliderPair)override;
	//コンストラクタから受け取った関数
	std::function<void(const int&)> AddGuardingObjectIdFunc;
	//アクティブ時間
	int activeCount;
	//アクティブ時間の最大数
	static const int ActiveCount;

	//生成される高さ 生成時のプレイヤーの高さに足す
	static const float CreatedHeightShield;
	//生成後に向かう高さ　生成時のプレイヤーの高さ
	int targetHeight;
	//浮遊時間 0になると落下する
	int floatingCount;
	//浮遊時間の最大数
	static const int FloatingCount;
};

