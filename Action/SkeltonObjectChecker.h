#pragma once
#include "GameObject.h"

/*
 @file SkeltonObjectChecker.h
 @brief �e�ƂȂ�I�u�W�F�N�g��ǐՂ��A�w�肳�ꂽ�^�O�����I�u�W�F�N�g�ƐڐG�����ۂɕω�����ڐG�t���O�ƐڐG����̍��W����������
	*/
class SkeltonObjectChecker :
	public GameObject
{
public:
	/*
	@param _parent �e�ƂȂ�I�u�W�F�N�g�B���̃I�u�W�F�N�g��ǐՂ���
	@param _pos _parent���痣��鋗���Boffset�Ƃ�����
	@param _colliderSize �Փ˂����m����͈�
	@param _pairTag ���A�N�V����������I�u�W�F�N�g��Tag
*/
	SkeltonObjectChecker(GameObject* _parent, Vector3 _pos, Vector3 _colliderSize, Tag _pairTag);
	~SkeltonObjectChecker();

	void UpdateGameObject(float _deltaTime)override;
	Vector3 GetColliderPairPosition() { return colliderPairPos; }

	/*
	@fn	�Q�b�^�[
	*/
	bool GetNoTouchingFlag() { return noTargetTouching; }
	
	/*
	 @fn �Z�b�^�[
	*/
	/*
	@exam ���]�����ۂɌĂ΂��
	*/
	void SetOffset(Vector3 _pos) { offset = _pos; }
private:
	void OnTriggerStay(ColliderComponent* colliderPair) override;
	void OnTriggerEnter(ColliderComponent* colliderPair)override;

	//�e�I�u�W�F�N�g
	GameObject* parent;
	//�e�I�u�W�F�N�g�Ƃ̍��W�̍�
	Vector3 offset;
	//�Փ˂̃��A�N�V�������s���Ώۂ�Tag
	Tag pairTag;
	//�Փˑ���̍��W
	Vector3 colliderPairPos;
	//�w�肳�ꂽ�^�O�ƐڐG���Ă��Ȃ��Ƃ��Ɍ��t���O
	bool noTargetTouching;
	//�w�肳�ꂽ�^�O�̃I�u�W�F�N�g�ƐڐG�����ۂɌ��B������Q�Ƃ��ăt���O�̃��Z�b�g���s�������߂�
	bool changed;
	class MeshComponent* meshComponent;
};


