#include "AnimationEnemyComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

AnimationEnemyComponent::AnimationEnemyComponent(GameObject * _owner, int updateOrder) :
	BoneAnimationBaseComponent(_owner, "Assets/SK_Mannequin.gpmesh", "Assets/SK_Mannequin.gpskel", updateOrder),
	animationName(EnemyAnimationName::Idle),
	move(false),
	attack(false),
	animDuration(0)
{
	moveAnim = RENDERER->GetAnimation("Assets/ThirdPersonRun.gpanim");
	idleAnim = RENDERER->GetAnimation("Assets/ThirdPersonIdle.gpanim");
	attackAnim = RENDERER->GetAnimation("Assets/ThirdPersonJump_Loop.gpanim");

	//�f�t�H���g�AIdle�ƂȂ�A�j���[�V�������ŏ��ɍĐ����邱��
	mMeshComp->PlayAnimation(idleAnim, 0.125f);
}

AnimationEnemyComponent::~AnimationEnemyComponent()
{
}

void AnimationEnemyComponent::UpdateAnimationComponent(float _deltaTime)
{
	switch (animationName)
	{
	case(EnemyAnimationName::Idle):
		if (move)
		{
			animationName = EnemyAnimationName::Move;
			animDuration = mMeshComp->PlayAnimation(moveAnim, 0.5f);
		}
		if (attack)
		{
			animationName = EnemyAnimationName::Attack;
			animDuration = mMeshComp->PlayAnimation(attackAnim, 0.5f);
		}
		if (animDuration < 0)
		{
			animDuration = mMeshComp->PlayAnimation(idleAnim, 0.5f);
		}
		break;
	case(EnemyAnimationName::Move):
		if (!move)
		{
			animationName = EnemyAnimationName::Idle;
			animDuration = mMeshComp->PlayAnimation(idleAnim, 0.5f);
		}
		if (attack)
		{
			animationName = EnemyAnimationName::Attack;
			animDuration = mMeshComp->PlayAnimation(attackAnim, 1.0f);
		}
		if (animDuration <= 0)
		{
			if (!move)
			{
				animationName = EnemyAnimationName::Idle;
				animDuration = mMeshComp->PlayAnimation(idleAnim, 0.5f);
			}
			else
			{
				animationName = EnemyAnimationName::Move;
				animDuration = mMeshComp->PlayAnimation(moveAnim, 0.5f);
			}
		}
		break;
	case(EnemyAnimationName::Attack):
		if (animDuration <= 0)
		{
			if (!move)
			{
				animationName = EnemyAnimationName::Idle;
				animDuration = mMeshComp->PlayAnimation(idleAnim, 0.5f);
			}
			else
			{
				animationName = EnemyAnimationName::Move;
				animDuration = mMeshComp->PlayAnimation(moveAnim, 0.5f);
			}
		}
		break;
	}
	animDuration-=0.005f;
}