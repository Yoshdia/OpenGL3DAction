#include "BoneAnimationBaseComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

BoneAnimationBaseComponent::BoneAnimationBaseComponent(GameObject * _owner, std::string _meshName, const char* _skeletalName, int updateOrder) :
	Component(_owner,updateOrder)
{
	mMeshComp = new SkeletalMeshComponent(_owner);
	mMeshComp->SetMesh(RENDERER->GetMesh(_meshName));
	mMeshComp->SetSkeleton(RENDERER->GetSkeleton(_skeletalName));
}

BoneAnimationBaseComponent::~BoneAnimationBaseComponent()
{
}

void BoneAnimationBaseComponent::Update(float _deltaTime)
{
	UpdateAnimationComponent(_deltaTime);
}
