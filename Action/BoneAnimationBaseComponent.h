#pragma once
#include "Component.h"


class BoneAnimationBaseComponent :
	public Component
{
public:
	/*
	@param _meshName ���b�V���ւ̃t�@�C���A�h���X
	@param _skeletalName �X�P���^���f�[�^�ւ̃t�@�C���A�h���X
	*/
	BoneAnimationBaseComponent(GameObject* _owner, int updateOrder=100);
	~BoneAnimationBaseComponent();

	void Update(float _deltaTime)override;
	virtual void UpdateAnimationComponent(float _deltaTime) {};
	void SetStartFlash() {startFlash = true; plusFlashColor = true;}
protected:
	class SkeletalMeshComponent* mMeshComp;
private:
	void Flash();
	bool startFlash;
	bool plusFlashColor;
	float flashColor;
};

