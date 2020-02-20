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

/*
@file PhysicsWorld.h
@brief ColliderComponent���Ǘ����Փ˂��s���N���X
*/
class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physicsWorld; }
	/*
	@fn PhysicsWorld����
	*/
	static void CreateInstance();
	/*
	@fn PhysicsWorld���
	*/
	static void DeleteInstance();

	/*
	@fn �������ꂽColliderComponent��colliders�֒ǉ�
	@param _collider PhysicsWorld�N���X�ɒǉ��������N���X
	*/
	void AddCollider(ColliderComponent* _collider);
	/*
   �@@fn ��������Ă���ColliuderComponent��colliders����폜
	@param _collider PhysicsWorld�N���X�������������N���X
  �@*/
	void RemoveCollider(ColliderComponent* _collider);
	/*
	@fn �Փ˔���
	@param _collider �Փ˂��s���AColliderComponent����Ă΂��Փˊ֐�
	*/
	void Collision(ColliderComponent * _collider);

private:
	PhysicsWorld() {};
	~PhysicsWorld() {};
	static PhysicsWorld* physicsWorld;

	//�������ꂽColliderComponent�S�ẴA�h���X���L��
	std::vector<ColliderComponent*> colliders;
};

/*
@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
@param _movableBox �ړ�����
@param _fixedBox �ړ����Ȃ�����
@param _calcFixVec �ړ����̂̕␳�����x�N�g��
*/
void calcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);
