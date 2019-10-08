#pragma once
#include "Component.h"
#include "Collision.h"

class GameObject;

class ColliderComponent : public Component
{
public:
    /**
    @param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
    @param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
    @param  �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
    */
	ColliderComponent(GameObject* _owner, int _updateOrder = 200,int _collisionOrder = 100);
	virtual ~ColliderComponent();

	int GetCollisionOrder() const { return collisionOrder; }

	//�I�u�W�F�N�g�����ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Sphere& _hirSphere) {}
	//�I�u�W�F�N�g�����ʂɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Plane& _hitPlane) {}
	//�I�u�W�F�N�g��AABB�ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const AABB& _hitBox) {}
	//�I�u�W�F�N�g���J�v�Z���ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Capsule& _hitCapsule) {}

	virtual void CollisionPause() = 0;
	virtual void CollisionActive() = 0;


private:
    //���̂𔺂������蔻������邩�ǂ���
	bool isTrigger;
	//���l���傫������D�悵�Ă߂荞�݂��瓮��������������i0�ȉ��͓������Ȃ��j
	int collisionOrder;
    //

};

