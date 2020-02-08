#pragma once
#include "Component.h"

/*
 @file BoneAnimationBaseComponent.h
 @brief �{�[���A�j���[�V�������s���N���X�̊��N���X
*/
class BoneAnimationBaseComponent :
	public Component
{
public:
	/*
	@fn ���b�V���f�[�^�N���X���m��
	*/
	BoneAnimationBaseComponent(GameObject* _owner, int updateOrder = 100);
	~BoneAnimationBaseComponent();

	/*
	 @fn �h���N���X�Ō��肷��֐��Ɣ����֐�Flash()���X�V����
	*/
	void Update(float _deltaTime)override;

protected:
	//���b�V���f�[�^�����L���`�悷��N���X
	class SkeletalMeshComponent* skeltalMeshComponent;
private:
	/*
	 @fn �h���N���X��̍X�V�֐�
	*/
	virtual void UpdateAnimationComponent(float _deltaTime) {};
	/*
	 @fn �������s���t���O�������Ă���Ƃ��A���b�V���J���[�𑝌��������b�V���f�[�^�ɐF����n��
	*/
	void Flash();
	//�������s����
	bool startFlash;
	//���̐F���甒�֐F�𑝉������Ă���t���O�@false=����
	bool plusFlashColor;
	//�F���@���̃N���X�͐F�𕡎G�ɐݒ肵�Ȃ��̂�float
	float flashColor;
public: //�Q�b�^�[�Z�b�^�[
	/*
	 @fn �����̊J�n
	*/
	void SetStartFlash() { startFlash = true; plusFlashColor = true; }
};

