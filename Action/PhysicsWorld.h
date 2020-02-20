#pragma once

/*
 @file PhysicsWorld.h
 @brief 生成されたColliderComponentへのアドレスを所持し、
		衝突判定を行いColliderComponentに衝突したことを伝えるクラス
 */

#include <vector>
#include "Math.h"
#include "Collision.h"
#include "GameObject.h"

class ColliderComponent;

/*
@file PhysicsWorld.h
@brief ColliderComponentを管理し衝突を行うクラス
*/
class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physicsWorld; }
	/*
	@fn PhysicsWorld生成
	*/
	static void CreateInstance();
	/*
	@fn PhysicsWorld解放
	*/
	static void DeleteInstance();

	/*
	@fn 生成されたColliderComponentをcollidersへ追加
	@param _collider PhysicsWorldクラスに追加したいクラス
	*/
	void AddCollider(ColliderComponent* _collider);
	/*
   　@fn 生成されているColliuderComponentをcollidersから削除
	@param _collider PhysicsWorldクラスから解放したいクラス
  　*/
	void RemoveCollider(ColliderComponent* _collider);
	/*
	@fn 衝突判定
	@param _collider 衝突を行う、ColliderComponentから呼ばれる衝突関数
	*/
	void Collision(ColliderComponent * _collider);

private:
	PhysicsWorld() {};
	~PhysicsWorld() {};
	static PhysicsWorld* physicsWorld;

	//生成されたColliderComponent全てのアドレスを記憶
	std::vector<ColliderComponent*> colliders;
};

/*
@fn 衝突したことが確定したとき、めり込みを戻す関数
@param _movableBox 移動物体
@param _fixedBox 移動しない物体
@param _calcFixVec 移動物体の補正差分ベクトル
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
