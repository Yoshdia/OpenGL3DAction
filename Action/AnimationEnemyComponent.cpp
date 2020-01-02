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
	spawn(false),
	animDuration(0)
{
	//メッシュ名以外にはgpskelの拡張指名をつけること
	std::string meshName = "";
	const char* skeletalName = "";
	const char* moveName = "";
	const char* idleName = "";
	const char* attackName = "";
	const char* spawnName = "";

	switch (_type)
	{
	case EnemyType::MeleeType:
		skeletalName = "Assets/Model/Skelton_King/skeleton_king_king.gpskel";

		meshName = "Assets/Model/Skelton_King/skeleton_king_king";
		moveName = "Assets/Model/Skelton_King/KingRun.gpanim";
		idleName = "Assets/Model/Skelton_King/KingIdle.gpanim";
		attackName = "Assets/Model/Skelton_King/KingAttack1.gpanim";

		spawnName = "Assets/Model/Skelton_King/spawn.gpanim";
		break;
	case EnemyType::RangeType:
		skeletalName = "Assets/Model/Skelton_Archer/skeleton_archer.gpskel";

		meshName = "Assets/Model/Skelton_Archer/skeleton_archer";
		moveName = "Assets/Model/Skelton_Archer/ArcherRun.gpanim";
		idleName = "Assets/Model/Skelton_Archer/ArcherIdle.gpanim";
		attackName = "Assets/Model/Skelton_Archer/ArcherChargeShoot.gpanim";
		break;
	case EnemyType::TankType:
		skeletalName = "Assets/Model/Giant/skeleton_grunt.gpskel";

		meshName = "Assets/Model/Giant/skeleton_grunt";
		moveName = "Assets/Model/Giant/run.gpanim";
		idleName = "Assets/Model/Giant/idle.gpanim";
		attackName = "Assets/Model/Giant/defaultAttack.gpanim";
		break;
	case EnemyType::MageType:
		skeletalName = "Assets/Model/Mage/skeleton_mage.gpskel";

		meshName = "Assets/Model/Mage/skeleton_mage";
		moveName = "Assets/Model/Mage/run.gpanim";
		idleName = "Assets/Model/Mage/idle.gpanim";
		attackName = "Assets/Model/Mage/defaultAttack.gpanim";

		spawnName = "Assets/Model/Mage/spawn.gpanim";
		summonAnim = RENDERER->GetAnimation("Assets/Model/Mage/summon.gpanim");
		break;
	default:

		break;
	}
	moveAnim = RENDERER->GetAnimation(moveName);
	idleAnim = RENDERER->GetAnimation(idleName);
	attackAnim = RENDERER->GetAnimation(attackName);
	spawnAnim = RENDERER->GetAnimation(spawnName);

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
		if (spawn)
		{
			animationName = EnemyAnimationName::Spawn;
			animDuration = mMeshComp->PlayAnimation(spawnAnim, 0.5f);
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
	case(EnemyAnimationName::Spawn):
		if (animDuration < 0)
		{
			animationName = EnemyAnimationName::Idle;
			if (summonAnim != nullptr)
			{
				animDuration = mMeshComp->PlayAnimation(summonAnim, 0.5f);
			}
			else
			{
				animDuration = mMeshComp->PlayAnimation(idleAnim, 0.5f);
			}
			spawn = false;
		}
		break;
	}
	animDuration -= 0.008f; 

}
