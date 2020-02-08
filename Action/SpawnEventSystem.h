#pragma once
#include "EventSystem.h"

/*
 @file SpawnEventSystem.h
 @brief 一定範囲にプレイヤーが侵入したときに入口を塞ぎMageをアクティブにする
*/
class SpawnEventSystem :
	public EventSystem
{
public:
	/*
	@param _pos 座標
	@param _wallPos プレイヤーが侵入してきたときにふさぐ壁の座標
	@param _goalPos MageEnemyが撃破されたときに削除する壁の座標
	*/
	SpawnEventSystem(const Vector3& _pos, const Vector3& _wallPos,const Vector3& _goalPos);
	~SpawnEventSystem();
private:
	/*
	@brief プレイヤーの侵入を検知したときにフラグを建てる
	*/
	void OnTriggerEnter(ColliderComponent* _pair)override;
	void UpdateEventObject() override ;
	//アクティブにするMageクラスポインタ
	class MageEnemy* mageEnemy;
	//デバッグ用、ヒットボックスの確認に
	class MeshComponent* meshComponent;
	//演出のスタートフラグ
	bool startDirecting;
	//侵入を検知した後に壁を生成する座標
	Vector3 wallPos;
public://ゲッターセッター
	/*
	@return MageEnemyのポインタ
	*/
	class MageEnemy* GetMageEnemy() { return mageEnemy; }

};

