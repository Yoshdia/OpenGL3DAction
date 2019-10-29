#pragma once

/*
 @file PhysicsWorld.h
 @brief �������ꂽColliderComponent�ւ̃A�h���X���������A
		�Փ˔�����s��ColliderComponent�ɏՓ˂������Ƃ�`����N���X
 */

#include <vector>
#include "Math.h"

class ColliderComponent;

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physicsWorld; }
	//PhysicsWorld�V���O���g���̐����Ɖ���֐�
	static void CreateInstance();
	static void DeleteInstance();

	/*
@fn �������ꂽColliderComponent��colliders�֒ǉ�
*/
	void AddCollider(ColliderComponent* collider);
	/*
   @fn ��������Ă���ColliuderComponent��colliders����폜
  */
	void RemoveCollider(ColliderComponent* collider);
	/*
	@fn �Փ˔���
	*/
	void Collision(ColliderComponent * collider);

private:
	PhysicsWorld() {};
	~PhysicsWorld() {};
	static PhysicsWorld* physicsWorld;

	//�������ꂽColliderComponent�S�ẴA�h���X���L��
	std::vector<ColliderComponent*> colliders;
};

