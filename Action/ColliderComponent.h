#pragma once
#include "Component.h"
#include "Math.h"
#include "GameObject.h"
#include <map>
#include<functional>
/*
 @file ColliderComponent��.h
 @brief �Փˋ@�\�����L����I�u�W�F�N�g�ɒǉ�������Component
 @detail Collider�N���X�ɂ���ĊǗ�����Փ˔��肪�s����
		�Փ˂ɕK�v�ȍ��W�A�����A�傫���Ȃǂ�GameObject����Collider�N���X�֎󂯓n���p�C�v�ɂ��g�p
		�Փ˂��������ObjectTagId�ƁA���ꂼ��Ƃ̐ڐG���(Enter,Stay,Exit)���L����GameObject�ւ̃��A�N�V�����֐����Ăяo��
 */
class ColliderComponent :
	public Component
{
public:
	/*
   @param owner �eGameObject�ւ̃|�C���^
   @param updateOrder ����Component�̍X�V����
   @param size �����蔻��̃T�C�Y(GameObject��Scale�Ƃ͈قȂ�)
   @param objectId GameObject�ɐU����ÓI�Ȏ��ʔԍ�
   @param tag GameObject�ɐU����ÓI�ȗ񋓌^
 */
	ColliderComponent(GameObject* owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)> TriggerEnter, std::function<void(ColliderComponent*)> TriggerStay, Tag tag);
	/*
	@param colliderPos �Փ˔��肪���݂��钆�S���W�@�eGameObject�̍��W�ɑ����Ďg�p����
	*/
	ColliderComponent(GameObject* owner, int updateOrder, Vector3 size, int objectId, std::function<void(ColliderComponent*)>TriggerEnter, std::function<void(ColliderComponent*)>TriggerStay, Tag tag, Vector3 colliderPos);

	~ColliderComponent();

	/*
   @fn Collider�N���X�ɂĐeObject���Փ˂�����Ăяo�����
   @brief �Փˑ���̎��ʎq�Ƒ���Ƃ̏Փˏ�Ԃ��L������
   @param colliderParter �Փˑ����ColliderComponent
   @detail Collider�N���X�ŐeObject���Փ˂������Ƃ�`�����A
		  �Փˏ�Ԃ�OF�ŏՓ˂��Ă����Փˏ��Ŕ��f���L������֐�
 */
	void OnCollision(ColliderComponent* colliderParter);

	/*
	@fn ��F�X�V�����֐�
	@brief ���ݐڐG���Ă��郊�X�g��O�t���[���ڐG���Ă������X�g�ֈڂ��Ȃǂ͂����ōs��
	*/
	void Update(float deltaTime) override;

	/*
	@fn �eObject�̃T�C�Y��Ԃ�
	*/
	//float GetScale();
	/*
	@fn �eObject�̍��W��Ԃ�
	*/
	Vector3 GetPosition();
	/*
	@fn �eObject�̎��ʔԍ���Ԃ�
	*/
	int GetId();
	/*
		@fn �����蔻��̃T�C�Y
	*/
	Vector3 GetCollisionSize() { return size; };
	void SetScale(Vector3 _scale){size=_scale;}

	Tag GetObjectTag();

	State GetState();

	bool GetDoCollision() {return doCollision;}
	void SetDoCollision(bool _flag) { doCollision = _flag; }
private:
	bool doCollision;
	//�Փ˔��肪���݂��钆�S���W�@�eGameObject�̍��W�ɑ����Ďg�p����
	Vector3 colliderPos;

	std::function<void(ColliderComponent*)> OnTriggerEnter;
	std::function<void(ColliderComponent*)> OnTriggerStay;

	/*
	@fn �ڐG�����I�u�W�F�N�g�B�Ƃ̐ڐG��Ԃ����ƂɐeGameObject�̃��A�N�V�����֐��ɐڐG�����Tag��n��
	*/
	void CollisionReaction(float deltaTime);
	/*
	@enum �ڐG��ԁAObjectTagId�ƂƂ���map�ŊǗ�����A���̐ڐG��Ԃ���ɐeObject�̃��A�N�V�����֐���I������
	*/
	enum CollisionState
	{
		//�OF�ŐڐG���Ă��炸�A�ڐG����
		Enter,
		//�OF�ł��ڐG���Ă���A�ڐG��
		Stay,
	};
	// �����蔻��̃T�C�Y(GameObject��Scale�Ƃ͈قȂ�)
	Vector3 size;
	//����F�ŐeObject�ƐڐG���Ă��鑊��Object�ƐڐG���
	std::map< ColliderComponent*, CollisionState> isCollision;
	//�OF�ŐeObject�ƐڐG���Ă�������Object�̎��ʎq
	std::map< ColliderComponent*, CollisionState> hadCollision;
};

