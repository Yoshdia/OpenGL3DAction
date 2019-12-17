#pragma once

/*
 @file PhysicsWorld.h
 @brief �������ꂽColliderComponent�ւ̃A�h���X���������A
		�Փ˔�����s��ColliderComponent�ɏՓ˂������Ƃ�`����N���X
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
	

	void MakeNoCollisionPair();
	//�������ꂽColliderComponent�S�ẴA�h���X���L��
	std::vector<ColliderComponent*> colliders;
	std::vector<std::pair<Tag, Tag>> noCollisionPairs;

	bool CheckDontCollisionPair(const Tag& lTag, const Tag& rTag);
};

////////////////////////////////////////////////////////////////////
// �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
// in    movableBox �ړ����� (ex �v���[���[)
// in    fixedBox   �ړ����Ȃ����́iex �u���b�N�j
// inout calcFixVec �ړ����̂̕␳�����x�N�g��
////////////////////////////////////////////////////////////////////
void calcCollisionFixVec(const AABB& movableBox, const AABB& fixedBox, Vector3& calcFixVec);
