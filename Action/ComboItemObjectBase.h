#pragma once
#include "GameObject.h"
#include <unordered_map>

/*
@enum ComboItemName
アイテムの名前
*/
enum ComboItemName
{
	NoComboItem=-1,
	RotateComboItem=0,
	ThrowComboItem=1,
	HammerComboItem=2,
	SlashSwordComboItem=3,
};

/*
@file ComboItemObjectBase.h
@brief プレイヤーが取得すると攻撃クラスを取得するアイテムの基底クラス
*/
class ComboItemObjectBase :
	public GameObject
{
public:
	/*
	@param _pos 座標
	@param _name アイテムの種類
	*/
	ComboItemObjectBase(const Vector3& _pos,const ComboItemName& _name);
	~ComboItemObjectBase();

	/*
	@fn 跳躍して落下する
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn オブジェクトIDでそのオブジェクトのアイテムを検索する
	@param _objectID オブジェクトID
	@return 検索結果
	*/
	static ComboItemName SearchComboId(const int& _objectId);
private:
	//オブジェクトIDごとのアイテム名
	static std::unordered_map<int,ComboItemName> comboItems;
	//地面を検知するクラス
	class SkeltonObjectChecker* noGround;
	//移動量
	Vector3 velocity;
};

