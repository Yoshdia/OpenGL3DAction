#include "AnimationEnemyComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"
#include <string>

/*
@fn�@�A�j���[�V�����⃂�f�������[�h����
@param _type �G�̎�ށ@���[�h���郂�f���⃍�[�h����A�j���[�V�������ς��
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
	//���b�V�����ȊO�ɂ�gpskel�̊g���w�������邱��
	std::string meshName = "";
	const char* skeletalName = "";
	const char* moveName = "";
	const char* idleName = "";
	const char* attackName = "";
	const char* spawnName = "";

	//�G�l�~�[�̎�ނɂ���ēǂݍ��ރ��b�V����A�j���[�V�����f�[�^��ύX
	switch (_type)
	{
	case EnemyType::MeleeType:
		skeletalName = "Assets/Model/Skelton_King/skeleton_king_king.gpskel";

		meshName = "Assets/Model/Skelton_King/skeleton_king_king";
		moveName = "Assets/Model/Skelton_King/KingRun.gpanim";
		idleName = "Assets/Model/Skelton_King/KingIdle.gpanim";
		attackName = "Assets/Model/Skelton_King/KingAttack1.gpanim";

		spawnName = "Assets/Model/Skelton_King/spawn.gpanim";
		spawnAnim = RENDERER->GetAnimation(spawnName);

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
		spawnAnim = RENDERER->GetAnimation(spawnName);
		actionAnim = RENDERER->GetAnimation("Assets/Model/Mage/summon.gpanim");
		actionAnimationSpeed=0.3f;
		stanAnim = RENDERER->GetAnimation("Assets/Model/Mage/hitForward.gpanim");
		break;
	case EnemyType::ShieldType:
		skeletalName = "Assets/Model/Shield/skeleton_swordsman.gpskel";

		meshName = "Assets/Model/Shield/skeleton_swordsman";
		moveName = "Assets/Model/Shield/run.gpanim";
		idleName = "Assets/Model/Shield/idle.gpanim";
		attackName = "Assets/Model/Shield/defaultAttack.gpanim";

		actionAnim = RENDERER->GetAnimation("Assets/Model/Shield/roar.gpanim");
		actionAnimationSpeed = 1.5f;
		break;
	default:
		break;
	}
	
	//�S�ẴG�l�~�[���p����A�j���[�V������ǂݍ���
	moveAnim = RENDERER->GetAnimation(moveName);
	idleAnim = RENDERER->GetAnimation(idleName);
	attackAnim = RENDERER->GetAnimation(attackName);
	skeltalMeshComponent->SetMesh(RENDERER->GetMesh(meshName + ".gpmesh"));
	skeltalMeshComponent->SetSkeleton(RENDERER->GetSkeleton(skeletalName));

	//�f�t�H���g�AIdle�ƂȂ�A�j���[�V�������ŏ��ɍĐ����邱��
	skeltalMeshComponent->PlayAnimation(idleAnim, 0.125f);
}

AnimationEnemyComponent::~AnimationEnemyComponent()
{
}

/*
@fn animationName�Ɗe�t���O���Q�Ƃ��ǂ̃A�j���[�V�������Đ����邩�����肵�Đ�����
*/
void AnimationEnemyComponent::UpdateAnimationComponent(float _deltaTime)
{
	switch (animationName)
	{
		//�ҋ@��ԁB���炩�̃A�j���[�V�����t���O�����Ƃ��̃A�j���[�V�����ɐ؂�ւ���
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
		//�ړ��A�j���[�V�����B�U����X�^���A�A�N�V�����ɔh��
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
		//�Đ����I�������Ƃ�
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
		//�U���A�j���[�V����
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
		//�������̃A�j���[�V����
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
		//�X�^�����̃A�j���[�V����
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
		//�A�N�V�����A�j���[�V����
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

void AnimationEnemyComponent::AllFlagReset()
{
	move = false;
	attack = false;
	spawn = false;
	stan = false;
	action = false;
}

void AnimationEnemyComponent::SetAction(bool _action)
{
	action = _action; 
	animDuration = skeltalMeshComponent->PlayAnimation(actionAnim, actionAnimationSpeed);

}
