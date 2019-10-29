#pragma once

/*
 @file PhysicsWorld.h
 @brief 生成されたColliderComponentへのアドレスを所持し、
		衝突判定を行いColliderComponentに衝突したことを伝えるクラス
 */

#include <vector>
#include "Math.h"

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

	//生成されたColliderComponent全てのアドレスを記憶
	std::vector<ColliderComponent*> colliders;
};

