#include "MageEnemy.h"
#include "AnimationEnemyComponent.h"
#include "RotateComponent.h"
#include "SkeltonObjectChecker.h"
#include "MainCameraObject.h"
#include "MeleeEnemy.h"
#include "DoSubActionMagesChild.h"

MageEnemy::MageEnemy(Vector3 _pos) :
	EnemyBase(_pos, Vector3(0.8f, 0.8f, 0.8f), EnemyType::MageType),
	attackState(false),
	directingCount(0),
	barrier(false),
	actionName(MageActionName::None),
	playerObject(this)
{
	animComponent->SetMove(false);
	moveDirection = EnemyMoveDirection::left;
	//playerSearcher = new SkeltonObjectChecker(this, Vector3(0, 0, 0), Vector3(500, 500, 500), Tag::PlayerTag);
	rotate->SetRotation(-90, Vector3::UnitY);
	meleeEnemy = new MeleeEnemy(_pos + Vector3(0, -250, 0));
	meleeEnemy->SetState(State::Dead);
	subActionClass = new DoSubActionMagesChild(this);
}

MageEnemy::~MageEnemy()
{
}

void MageEnemy::PausingUpdateGameObject()
{
	mainCamera->UpdateGameObject(0.06f);
	animComponent->UpdateAnimationComponent(0.6f);
	animComponent->SetSpawn(false);
	if (directingCount == 3)//220
	{
		rotate->SetRotation(90, Vector3::UnitY);
		meleeEnemy->SetState(State::Active);
		meleeEnemy->SpawnSummoned();
		mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -350), meleeEnemy->GetPosition());
		directingCount++;
	}
	else if (directingCount >= 5)//530
	{
		pauzingUpdate = false;
		actionName = MageActionName::FloatShot;
		subActionClass->StartFloating();
	}
	else
	{
		directingCount++;
	}
}

void MageEnemy::SetAttackState(GameObject* _playerObject)
{
  	playerObject = _playerObject;
	attackState = true;
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -400), position);
	animComponent->SetSpawn(true);
}

void MageEnemy::UpdateEnemyObject(float _deltaTime)
{
	printf("%f\n", position.y);
	//�v���C���[���˒��������ɓ���U���Ԑ��ɓ����Ă��邩
	if (attackState)
	{
		if (playerObject == nullptr)
		{
			return;
		}
		//�ǐՑΏۂ̍��W���擾
		Vector3 target = playerObject->GetPosition();
		//�v���C���[�Ƃ�x���W�Ԃ̋������v�Z
		float playerDistance = position.x - target.x;
		switch (actionName)
		{
		case(MageActionName::FloatShot):
			//�v���C���[�̈ʒu�Ō�����ύX
			if (playerDistance >= 0)
			{
				moveDirection = EnemyMoveDirection::left;
			}
			else
			{
				moveDirection = EnemyMoveDirection::right;
			}
			break;
		case(MageActionName::SkillCharge):
			break;
		case(MageActionName::Stanning):
			break;
		}
		AliveLoiteringEnemyCheck();
	}
}

void MageEnemy::AliveLoiteringEnemyCheck()
{
	if (meleeEnemy->GetState() == State::Dead&&attackState)
	{
		printf("outi!!!!\n");
		attackState = false;
		barrier = false;
	}
	else
	{
		barrier = true;
	}
}

void MageEnemy::DeadEvent()
{
}

void MageEnemy::HitPlayerAttack(const Vector3 & _pairPos)
{
	if (!barrier)
	{
		hitPoint--;
	}
	else
	{

	}
}
