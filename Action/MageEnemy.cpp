#include "MageEnemy.h"
#include "AnimationEnemyComponent.h"
#include "RotateComponent.h"
#include "SkeltonObjectChecker.h"
#include "MainCameraObject.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"
#include "DoSubActionMagesChild.h"
#include "StraightMagicBullet.h"
#include "FloatParticleEffect.h"
#include "DamageSquareEffect.h"
#include "ParticleObject.h"
#include "BombParticleEffect.h"

const int MageEnemy::StanCount = 250;
const int MageEnemy::ChargeCount = 5;
const int MageEnemy::ShotInterval = 250;

/*
@param _pos ���W
*/
MageEnemy::MageEnemy(Vector3 _pos) :
	EnemyBase(_pos, Vector3(0.8f, 0.8f, 0.8f), EnemyType::MageType),
	attackState(false),
	directingCount(0),
	barrier(false),
	actionName(MageActionName::None),
	playerObject(this),
	chargeCount(0),
	stanCount(0),
	popLoiteringEnemyPosition(Vector3::Zero),
	shotInterval(0)
{
	hitPoint = 40;
	goalWallObject = nullptr;
	animComponent->SetMove(false);
	moveDirection = EnemyMoveDirection::left;
	rotate->SetRotation(-90, Vector3::UnitY);
	popLoiteringEnemyPosition = _pos + Vector3(0, -250, 0);
	meleeEnemy = new MeleeEnemy(popLoiteringEnemyPosition);
	meleeEnemy->SetState(State::Dead);
	rangeEnemy = new RangeEnemy(popLoiteringEnemyPosition);
	rangeEnemy->SetState(State::Dead);
	subActionClass = new DoSubActionMagesChild(this);
	animComponent->SetSubDuration(0.006f);
	guardParticle = new ParticleObject(Vector3(0, 0, 100), "Assets/Image/Effect/damageSquare.png", 70.0f, 100);
	guardParticle->SetState(State::Dead);
}

MageEnemy::~MageEnemy()
{
}

/*
@brief �Q�[���I�u�W�F�N�g��~���ɍX�V�A���g�ɃJ�����������A�j���[�V�������Đ��A�G����PoP������
*/
void MageEnemy::PausingUpdateGameObject()
{
	if (pauzingEvent == PauzingEvent::SummonMageEvent)
	{
		mainCamera->UpdateGameObject(0.06f);
		animComponent->UpdateAnimationComponent(0.6f);
		animComponent->SetSpawn(false);
		if (directingCount == 290)//220
		{
			rotate->SetRotation(90, Vector3::UnitY);
			meleeEnemy->SpawnSummoned(popLoiteringEnemyPosition, 5);
			new FloatParticleEffect(Vector3(45, 0, 0) + popLoiteringEnemyPosition, Vector3(0, 2, 0));
			new FloatParticleEffect(Vector3(-45, 0, 0) + popLoiteringEnemyPosition, Vector3(0, 2, 0));
			mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -350), meleeEnemy->GetPosition());
			directingCount++;
		}
		else if (directingCount >= 460)//530
		{
			//meleeEnemy->SetPosition(popLoiteringEnemyPosition);
			pauzingEvent = PauzingEvent::NoneEvent;
			actionName = MageActionName::FloatShot;
			animComponent->SetSubDuration(0.017f);
		}
		else if (directingCount > 320)
		{
			meleeEnemy->ExceptionUpdate();
			directingCount++;

		}
		else
		{
			directingCount++;
		}
	}
}

/*
@brief �ҋ@��Ԃ���퓬��Ԃɓ���֐��@��������
*/
void MageEnemy::SetAttackState(GameObject* _playerObject)
{
	playerObject = _playerObject;
	attackState = true;
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -400), position);
	animComponent->SetSpawn(true);
}

/*
@fn ���(MageActionName)���Ƃ̃A�N�V�������s��
*/
void MageEnemy::UpdateEnemyObject(float _deltaTime)
{
	//�v���C���[���˒��������ɓ���U���Ԑ��ɓ����Ă��邩
	if (attackState)
	{
		if (playerObject == nullptr)
		{
			return;
		}
		guardParticle->SetPosition(position+Vector3(0,80,-35));
		//�ǐՑΏۂ̍��W���擾
		Vector3 target = playerObject->GetPosition();
		//�v���C���[�Ƃ�x���W�Ԃ̋������v�Z
		float playerDistance = position.x - target.x;

		switch (actionName)
		{
		case(MageActionName::FloatShot):
			guardParticle->SetState(State::Active);
			//�v���C���[�̈ʒu�Ō�����ύX
			if (playerDistance >= 0)
			{
				moveDirection = EnemyMoveDirection::left;
			}
			else
			{
				moveDirection = EnemyMoveDirection::right;
			}
			subActionClass->MoveHorizontal();
			subActionClass->HuwaHuwa();
			Shot(target);
			AliveLoiteringEnemyCheck();
			break;
		case(MageActionName::SkillCharge):
			animComponent->SetStan(false);
			animComponent->SetAttack(false);
			animComponent->SetMove(false);
			animComponent->SetSpawn(false);
			if (chargeCount <= 0)
			{
				animComponent->SetAction(true);
				meleeEnemy->SpawnSummoned(popLoiteringEnemyPosition + Vector3(100, 0, 0), 9);
				new FloatParticleEffect(Vector3(30, 0, 0) + popLoiteringEnemyPosition + Vector3(100, 0, 0), Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-30, 0, 0) + popLoiteringEnemyPosition + Vector3(100, 0, 0), Vector3(0, 2, 0));
				rangeEnemy->SpawnSummoned(popLoiteringEnemyPosition + Vector3(-100, 0, 0), 9);
				new FloatParticleEffect(Vector3(30, 0, 0) + popLoiteringEnemyPosition + Vector3(-100, 0, 0), Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-30, 0, 0) + popLoiteringEnemyPosition + Vector3(-100, 0, 0), Vector3(0, 2, 0));
				subActionClass->StartFloating();
				actionName = MageActionName::Skill;
			}
			else
			{
				chargeCount--;
			}
			break;
		case(MageActionName::Skill):
			animComponent->SetSubDuration(0.018f);
			guardParticle->SetState(State::Active);
			barrier = true;
			if (subActionClass->EndFloatDrop())
			{
				actionName = MageActionName::FloatShot;
			}
			break;
		case(MageActionName::Stanning):
			if (stanCount <= 0)
			{
				actionName = MageActionName::SkillCharge;
				chargeCount = ChargeCount;
			}
			else
			{
				stanCount--;
			}
			break;
		}
	}
}
/*
@fn ���������G���������Ă��邩�B���Ă��Ȃ��Ƃ��X�^������B
*/
void MageEnemy::AliveLoiteringEnemyCheck()
{
	if ((meleeEnemy->GetState() == State::Dead && rangeEnemy->GetState() == State::Dead) && attackState)
	{
		subActionClass->StartDroppingDown();
		barrier = false;
		actionName = MageActionName::Stanning;
		guardParticle->SetState(State::Dead);
		Vector3 effectPos = Vector3(position.x, position.y + 50, position.z);
		new BombParticleEffect(effectPos, Vector3(10, 20, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 20, 0));
		new BombParticleEffect(effectPos, Vector3(10, 18, 0));
		new BombParticleEffect(effectPos, Vector3(10, 14, 0));
		new BombParticleEffect(effectPos, Vector3(10, 11, 0));
		new BombParticleEffect(effectPos, Vector3(10, 8, 0));
		new BombParticleEffect(effectPos, Vector3(10, 5, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 18, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 14, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 1, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 8, 0));
		new BombParticleEffect(effectPos, Vector3(-10, 5, 0));
		if (attackObject != nullptr)
		{
			attackObject->SetState(State::Dead);
		}
		stanCount = StanCount;
		animComponent->SetStan(true);
		animComponent->SetSubDuration(0.005f);
	}
	else
	{
		barrier = true;
	}
}
/*
@fn ���j�C�x���g
*/
void MageEnemy::DeadEvent()
{
	goalWallObject->SetState(State::Dead);
}

/*
@fn �U�����ꂽ�Ƃ��B���������G���������Ă���Ƃ��U��������Ȃ�
*/
void MageEnemy::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	if (!barrier)
	{
		hitPoint -= _power;
		animComponent->SetStartFlash();

	}
	else
	{
		printf("Mages Guard HitPoint : %d \n", hitPoint);
		new DamageSquareEffect(position + Vector3(0, 50, 0));
	}
}

/*
@fn �v���C���[�Ɍ����Ēe�𔭎˂���
@param _target �ڕW���W
*/
void MageEnemy::Shot(const Vector3& target)
{
	if (shotInterval <= 0)
	{
		shotInterval = ShotInterval;
		attackObject = new StraightMagicBullet(position, target, 100);
		animComponent->SetAttack(true);
	}
	else
	{
		animComponent->SetAttack(false);
		shotInterval--;
	}
}
