#include "BoneAnimationBaseComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

BoneAnimationBaseComponent::BoneAnimationBaseComponent(GameObject * _owner, int updateOrder) :
	Component(_owner,updateOrder)
{
	mMeshComp = new SkeletalMeshComponent(_owner);

}

BoneAnimationBaseComponent::~BoneAnimationBaseComponent()
{
}

void BoneAnimationBaseComponent::Update(float _deltaTime)
{
	UpdateAnimationComponent(_deltaTime);
}
