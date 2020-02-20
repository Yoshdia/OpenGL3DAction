#include "AnimationEnemyComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"
#include <string>

/*
@fn　アニメーションやモデルをロードする
@param _type 敵の種類　ロードするモデルやロードするアニメーションが変わる
*/
AnimationEnemyComponent::AnimationEnemyComponent(GameObject * _owner, EnemyType _type, int updateOrder) :
	BoneAnimationBaseComponent(_owner, updateOrder),
	animationName(EnemyAnimationName::Idle),
	move(false),
	attack(false),
	spawn(false),
	animDuration(0),
	action(false),
	subAnimDuration(0.0001f),
	actionAnimationSpeed(0.3f)
{
	//メッシュ名以外にはgpskelの拡張指名をつけること
	std::string meshName = "";

	const char* skeletalName = "";
	const char* moveName = "";
	const char* idleName = "";
	const char* attackName = "";
	const char* spawnName = "";

	//エネミーの種類によって読み込むメッシュやアニメーションデータを変更
	switch (_type)
	{
	case EnemyType::MeleeType:
		meshName = "Assets/Model/Skelton_King/skeleton_king_king";

		skeletalName = "Assets/Model/Skelton_King/skeleton_king_king.gpskel";
		moveName = "Assets/Model/Skelton_King/KingRun.gpanim";
		idleName = "Assets/Model/Skelton_King/KingIdle.gpanim";
		attackName = "Assets/Model/Skelton_King/KingAttack1.gpanim";
		spawnName = "Assets/Model/Skelton_King/spawn.gpanim";
		spawnAnim = RENDERER->GetAnimation(spawnName);
		break;
	case EnemyType::RangeType:
		meshName = "Assets/Model/Skelton_Archer/skeleton_archer";

		skeletalName = "Assets/Model/Skelton_Archer/skeleton_archer.gpskel";
		moveName = "Assets/Model/Skelton_Archer/ArcherRun.gpanim";
		idleName = "Assets/Model/Skelton_Archer/ArcherIdle.gpanim";
		attackName = "Assets/Model/Skelton_Archer/ArcherChargeShoot.gpanim";
		break;
	case EnemyType::TankType:
		meshName = "Assets/Model/Giant/skeleton_grunt";

		skeletalName = "Assets/Model/Giant/skeleton_grunt.gpskel";
		moveName = "Assets/Model/Giant/run.gpanim";
		idleName = "Assets/Model/Giant/idle.gpanim";
		attackName = "Assets/Model/Giant/defaultAttack.gpanim";
		break;
	case EnemyType::MageType:
		meshName = "Assets/Model/Mage/skeleton_mage";

		skeletalName = "Assets/Model/Mage/skeleton_mage.gpskel";
		moveName = "Assets/Model/Mage/run.gpanim";
		idleName = "Assets/Model/Mage/idle.gpanim";
		attackName = "Assets/Model/Mage/defaultAttack.gpanim";
		spawnName = "Assets/Model/Mage/spawn.gpanim";
		spawnAnim = RENDERER->GetAnimation(spawnName);
		actionAnim = RENDERER->GetAnimation("Assets/Model/Mage/summon.gpanim");
		//召喚を行う特殊アクションのアニメーション速度
		actionAnimationSpeed=1.0f;
		stanAnim = RENDERER->GetAnimation("Assets/Model/Mage/hitForward.gpanim");
		break;
	case EnemyType::ShieldType:
		skeletalName = "Assets/Model/Shield/skeleton_swordsman.gpskel";

		meshName = "Assets/Model/Shield/skeleton_swordsman";
		moveName = "Assets/Model/Shield/run.gpanim";
		idleName = "Assets/Model/Shield/idle.gpanim";
		attackName = "Assets/Model/Shield/defaultAttack.gpanim";
		actionAnim = RENDERER->GetAnimation("Assets/Model/Shield/roar.gpanim");
		//攻撃を防御したときのアニメーション速度
		actionAnimationSpeed = 1.5f;
		break;
	default:
		break;
	}
	
	//全てのエネミーが用いるアニメーションを読み込む
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh(meshName + ".gpmesh"));
	moveAnim = RENDERER->GetAnimation(moveName);
	idleAnim = RENDERER->GetAnimation(idleName);
	attackAnim = RENDERER->GetAnimation(attackName);
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton(skeletalName));

	//デフォルト、Idleとなるアニメーションを最初に再生すること
	skeltalMeshComponent->PlayAnimation(idleAnim, 0.125f);
}

AnimationEnemyComponent::~AnimationEnemyComponent()
{
}

/*
@fn animationNameと各フラグを参照しどのアニメーションを再生するかを決定し再生する
*/
void AnimationEnemyComponent::UpdateAnimationComponent(float _deltaTime)
{
	switch (animationName)
	{
		//待機状態。何らかのアニメーションフラグが建つとそのアニメーションに切り替える
	case(EnemyAnimationName::Idle):
		if (move)
		{
			animationName = EnemyAnimationName::Move;
			animDuration = skeltalMeshComponent->PlayAnimation(moveAnim, 0.5f);
		}
		if (attack)
		{
			animationName = EnemyAnimationName::Attack;
			animDuration = skeltalMeshComponent->PlayAnimation(attackAnim, 1.0f);
		}
		if (spawn)
		{
			animationName = EnemyAnimationName::Spawn;
			animDuration = skeltalMeshComponent->PlayAnimation(spawnAnim, 0.6f);
		}
		if (stan)
		{
			animationName = EnemyAnimationName::Stan;
			animDuration = skeltalMeshComponent->PlayAnimation(stanAnim, 0.3f);
		}
		if (action)
		{
			animationName = EnemyAnimationName::Action;
			animDuration = skeltalMeshComponent->PlayAnimation(actionAnim, actionAnimationSpeed);
		}
		if (animDuration < 0)
		{
			animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
		}
		break;
		//移動アニメーション。攻撃やスタン、アクションに派生
	case(EnemyAnimationName::Move):
		if (!move)
		{
			animationName = EnemyAnimationName::Idle;
			animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
		}
		if (attack)
		{
			animationName = EnemyAnimationName::Attack;
			animDuration = skeltalMeshComponent->PlayAnimation(attackAnim, 1.0f);
		}
		if (stan)
		{
			animationName = EnemyAnimationName::Stan;
			animDuration = skeltalMeshComponent->PlayAnimation(stanAnim, 0.1f);
		}
		if (action)
		{
			animationName = EnemyAnimationName::Action;
			animDuration = skeltalMeshComponent->PlayAnimation(actionAnim, actionAnimationSpeed);
		}
		//再生が終了したとき
		if (animDuration <= 0)
		{
			if (!move)
			{
				animationName = EnemyAnimationName::Idle;
				animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
			}
			else
			{
				animationName = EnemyAnimationName::Move;
			}
		}
		break;
		//攻撃アニメーション
	case(EnemyAnimationName::Attack):
		if (animDuration <= 0)
		{
			if (!move)
			{
				animationName = EnemyAnimationName::Idle;
				animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
			}
			else
			{
				animationName = EnemyAnimationName::Move;
				animDuration = skeltalMeshComponent->PlayAnimation(moveAnim, 0.5f);
			}
		}
		if (stan)
		{
			animationName = EnemyAnimationName::Stan;
			animDuration = skeltalMeshComponent->PlayAnimation(stanAnim, 0.3f);
		}
		if (spawn)
		{
			animationName = EnemyAnimationName::Spawn;
			animDuration = skeltalMeshComponent->PlayAnimation(spawnAnim, 0.6f);
		}
		break;
		//生成時のアニメーション
	case(EnemyAnimationName::Spawn):
		if (animDuration < 0)
		{
			animationName = EnemyAnimationName::Idle;
			if (actionAnim != nullptr)
			{
				animDuration = skeltalMeshComponent->PlayAnimation(actionAnim, actionAnimationSpeed);
			}
			else
			{
				animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
			}
			spawn = false;
		}
		break;
		//スタン中のアニメーション
	case(EnemyAnimationName::Stan):
		if (animDuration < 0)
		{
			if (stan)
			{
				animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.1f);
			}
		}
		if (!stan)
		{
			animationName = EnemyAnimationName::Idle;
			animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
		}
		break;
		//アクションアニメーション
	case(EnemyAnimationName::Action):
		if (animDuration < 0)
		{
			action = false;
			animationName = EnemyAnimationName::Idle;
			animDuration = skeltalMeshComponent->PlayAnimation(idleAnim, 0.5f);
		}
		if (stan)
		{
			animationName = EnemyAnimationName::Stan;
			animDuration = skeltalMeshComponent->PlayAnimation(stanAnim, 0.3f);
		}
		if (attack)
		{
			animationName = EnemyAnimationName::Attack;
			animDuration = skeltalMeshComponent->PlayAnimation(attackAnim, 1.0f);
		}
	}
	animDuration -= subAnimDuration;
}

/*
@fn 全てのアニメーションフラグを倒す
*/
void AnimationEnemyComponent::AllFlagReset()
{
	move = false;
	attack = false;
	spawn = false;
	stan = false;
	action = false;
}
/*
@fn アニメーションフラグをセットしアクションアニメーションを再生
*/
void AnimationEnemyComponent::SetAction(bool _action)
{
	action = _action; 
	animDuration = skeltalMeshComponent->PlayAnimation(actionAnim, actionAnimationSpeed);

}
