#include "BoneAnimationBaseComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

BoneAnimationBaseComponent::BoneAnimationBaseComponent(GameObject * _owner, int updateOrder) :
	Component(_owner,updateOrder),
	startFlash(false),
	flashColor(0),
	plusFlashColor(false)
{
	mMeshComp = new SkeletalMeshComponent(_owner);
}

BoneAnimationBaseComponent::~BoneAnimationBaseComponent()
{
}

void BoneAnimationBaseComponent::Update(float _deltaTime)
{
	Flash();
	UpdateAnimationComponent(_deltaTime);
}

void BoneAnimationBaseComponent::Flash()
{
	if (startFlash)
	{
		if (plusFlashColor)
		{
			if (flashColor > 1.0f)
			{
				flashColor = 1.0f;
				plusFlashColor = false;
			}
			else
			{
				flashColor += 0.2f;
			}
		}
		else
		{
			if (flashColor < 0)
			{
				flashColor = 0;
				startFlash = false;
			}
			else
			{
				flashColor -= 0.2f;
			}
		}
		mMeshComp->SetColor(Vector3(flashColor, flashColor, flashColor));
	}
}
