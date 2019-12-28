#include "AnimationEnemyComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"
#include <string>

AnimationEnemyComponent::AnimationEnemyComponent(GameObject * _owner, EnemyType _type, int updateOrder) :
	BoneAnimationBaseComponent(_owner, updateOrder),
	animationName(EnemyAnimationName::Idle),
	move(false),
	attack(false),
	animDuration(0)
{
	//メッシュ名以外にはgpskelの拡張指名をつけること
	std::string meshName = "";
	const char* skeletalName = "";
	const char* moveName = "";
	const char* idleName = "";
	const char* attackName = "";

	switch (_type)
	{
	case EnemyType::MeleeType:
		skeletalName = "Assets/Model/Skelton_King/skeleton_king_king.gpskel";

		meshName = "Assets/Model/Skelton_King/skeleton_king_king";
		moveName = "Assets/Model/Skelton_King/KingRun.gpanim";
		idleName = "Assets/Model/Skelton_King/KingIdle.gpanim";
		attackName = "Assets/Model/Skelton_King/KingAttack1.gpanim";
		break;
	case EnemyType::RangeType:
		skeletalName = "Assets/Model/Skelton_Archer/skeleton_archer.gpskel";

		meshName = "Assets/Model/Skelton_Archer/skeleton_archer";
		moveName = "Assets/Model/Skelton_Archer/ArcherRun.gpanim";
		idleName = "Assets/Model/Skelton_Archer/ArcherIdle.gpanim";
		attackName = "Assets/Model/Skelton_Archer/ArcherChargeShoot.gpanim";
		break;
	default:

		break;
	}
	moveAnim = RENDERER->GetAnimation(moveName);
	idleAnim = RENDERER->GetAnimation(idleName);
	attackAnim = RENDERER->GetAnimation(attackName);

	mMeshComp->SetMesh(RENDERER->GetMesh(meshName + ".gpmesh"));
	mMeshComp->SetSkeleton(RENDERER->GetSkeleton(skeletalName));

	//デフォルト、Idleとなるアニメーションを最初に再生すること
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
				//animDuration = mMeshComp->PlayAnimation(moveAnim, 0.5f);
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
	animDuration -= 0.020f;

}
