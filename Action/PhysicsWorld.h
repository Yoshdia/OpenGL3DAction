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

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physicsWorld; }
	//PhysicsWorldシングルトンの生成と解放関数
	static void CreateInstance();
	static void DeleteInstance();

	/*
@fn 生成されたColliderComponentをcollidersへ追加
*/
	void AddCollider(ColliderComponent* collider);
	/*
   @fn 生成されているColliuderComponentをcollidersから削除
  */
	void RemoveCollider(ColliderComponent* collider);
	/*
	@fn 衝突判定
	*/
	void Collision(ColliderComponent * collider);

private:
	PhysicsWorld() {};
	~PhysicsWorld() {};
	static PhysicsWorld* physicsWorld;
	

	void MakeNoCollisionPair();
	//生成されたColliderComponent全てのアドレスを記憶
	std::vector<ColliderComponent*> colliders;
	std::vector<std::pair<Tag, Tag>> noCollisionPairs;

	bool CheckDontCollisionPair(const Tag& lTag, const Tag& rTag);
};

////////////////////////////////////////////////////////////////////
// 衝突したことが確定したとき、めり込みを戻す関数
// in    movableBox 移動物体 (ex プレーヤー)
// in    fixedBox   移動しない物体（ex ブロック）
// inout calcFixVec 移動物体の補正差分ベクトル
////////////////////////////////////////////////////////////////////
void calcCollisionFixVec(const AABB& movableBox, const AABB& fixedBox, Vector3& calcFixVec);
