#pragma once
#include "GameObject.h"

/*
 @file SkeltonObjectChecker.h
 @brief 親となるオブジェクトを追跡し、指定されたタグをもつオブジェクトと接触した際に変化する接触フラグと接触相手の座標を所持する
	*/
class SkeltonObjectChecker :
	public GameObject
{
public:
	/*
	@param _parent 親となるオブジェクト。このオブジェクトを追跡する
	@param _pos _parentから離れる距離。offsetとも言う
	@param _colliderSize 衝突を検知する範囲
	@param _pairTag リアクションをするオブジェクトのTag
*/
	SkeltonObjectChecker(GameObject* _parent, Vector3 _pos, Vector3 _colliderSize, Tag _pairTag);
	~SkeltonObjectChecker();

	void UpdateGameObject(float _deltaTime)override;
	Vector3 GetColliderPairPosition() { return colliderPairPos; }

	/*
	@fn	ゲッター
	*/
	bool GetNoTouchingFlag() { return noTargetTouching; }
	
	/*
	 @fn セッター
	*/
	/*
	@exam 反転した際に呼ばれる
	*/
	void SetOffset(Vector3 _pos) { offset = _pos; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	//親オブジェクト
	GameObject* parent;
	//親オブジェクトとの座標の差
	Vector3 offset;
	//衝突のリアクションを行う対象のTag
	Tag pairTag;
	//衝突相手の座標
	Vector3 colliderPairPos;
	//指定されたタグと接触していないときに建つフラグ
	bool noTargetTouching;
	//指定されたタグのオブジェクトと接触した際に建つ。これを参照してフラグのリセットを行うか決める
	bool changed;
	class MeshComponent* meshComponent;
};


