#pragma once
#include "Component.h"
#include <string>


class BoneAnimationBaseComponent :
	public Component
{
public:
	/*
	@param _meshName メッシュへのファイルアドレス
	@param _skeletalName スケルタルデータへのファイルアドレス
	*/
	BoneAnimationBaseComponent(GameObject* _owner, std::string _meshName, const char* _skeletalName,int updateOrder=100);
	~BoneAnimationBaseComponent();

	void Update(float _deltaTime)override;
	virtual void UpdateAnimationComponent(float _deltaTime) {};
protected:
	class SkeletalMeshComponent* mMeshComp;

};

