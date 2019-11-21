#pragma once
#include "Component.h"
#include <vector>

class ShieldWeapon;

/*
 @file GuardPlayerComponent.h
 @brief 盾を生成し、盾と接触した敵武器のidを記憶する
*/
class GuardPlayerComponent :
	public Component
{
public:
	GuardPlayerComponent(GameObject* owner, int updateOrder);
	~GuardPlayerComponent();

	/*
	@fn 防御中のオブジェクトの中から検索する
	@param _id 検索したいオブジェクト
	@return 検索結果 あった...true
	*/
	bool SearchObjectId(const int& _id);
	/*
	@fn 防御アクション
	@brief 盾の初期化を行う
	@return アクションの硬直時間
	*/
	float Guard();
	/*
	@brief 盾が非アクティブ状態でないかを調べ、そうだったとき防御リストをリセットする
	*/
	void Update(float _deltaTime)override;
private:
	//プレイヤーに付与するアクション硬直時間
	static const float canNotActionTime;
	//防御中オブジェクトのid
	std::vector<int> guardingObjectIds;
	/*
	@fn 防御したオブジェクトの追加
	@brief ShieldWeaponから呼ばれ、既に追加済みでないかを調べて追加する
	*/
	void AddGuardingObjectId(const int& _id);
	//カメラから見て右にある盾
	ShieldWeapon* rightShield;
	//カメラから見て左にある盾
	ShieldWeapon* leftShield;
	//左右の盾間の隙間
	static const float ShieldSpace;
};

