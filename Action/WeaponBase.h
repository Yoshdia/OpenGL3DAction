#pragma once
#include "GameObject.h"
#include <string>
#include <unordered_map>

/*
@file WeaponBase.h
@brief プレイヤーの武器基底クラス。生成直後は白く、元の色に戻っていく
*/
class WeaponBase :
	public GameObject
{
public:
	/*
	@param _pos 座標
	@param _waitCount 待機時間
	@param _lifeCount 生存時間
	@param _direction 向き
	@param _tag タグ
	@param _weaponName 武器の威力
	@param _colliderSize 衝突範囲
	@param _colorSub 白い色から元の色に戻るまでの速度
	@param _meshFileName メッシュデータのアドレス
	@param _skeletalFileName スケルトンデータのアドレス
	*/
	WeaponBase(const Vector3& _pos, const int& _waitCount, const int& _lifeCount, const float& _direction, const Tag& _tag,const int& _weaponName, const Vector3& _colliderSize,const float& _colorSub, const std::string & _meshFileName, const char * _skeletalFileName);
	~WeaponBase();
	/*
	@fn 元の色に戻す
	*/
	void UpdateGameObject(float _deltaTime)override;
	/*
	@fn オブジェクトIDを基に威力を検索する
	@param _objectId オブジェクトID
	@return 威力
	*/
	static int SearchWeaponPower(const int& _objectId);
protected:
	//回転を補助するクラス
	class RotateComponent* rotateComponent;
	//向き
	int direction;
	//活動時間
	int activeCount;
	/*
	@fn 派生クラスごとの更新関数
	*/
	virtual void UpdateWeaponGameObject(float _deltaTime) {};
	//衝突を行うか
	bool doCollision;
private:
	//オブジェクトIDごとの威力を記憶
	static std::unordered_map<int,int> weapons;
	//衝突判定クラス
	class ColliderComponent* colliderComponent;
	//スケルトンクラス
	class SkeletalMeshComponent* skeletalComponent;
	//待機時間
	int waitCount;
	//生存時間
	int lifeCount;
	//現在の色
	float color ;
	//色の減少値
	float colorSub;
};

