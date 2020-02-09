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

const int MageEnemy::StanCount = 300;
const int MageEnemy::ChargeCount = 10;
const int MageEnemy::ShotInterval = 250;

/*
@param _pos 座標
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
	hitPoint = 50;
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
	animComponent->SetSubDuration(0.005f);
}

MageEnemy::~MageEnemy()
{
}

/*
@brief ゲームオブジェクト停止中に更新、自身にカメラを向けアニメーションを再生、雑魚をPoPさせる
*/
void MageEnemy::PausingUpdateGameObject()
{
	if (pauzingEvent == PauzingEvent::SummonMageEvent)
	{
		mainCamera->UpdateGameObject(0.06f);
		animComponent->UpdateAnimationComponent(0.6f);
		animComponent->SetSpawn(false);
		if (directingCount == 320)//220
		{
			rotate->SetRotation(90, Vector3::UnitY);
			meleeEnemy->SpawnSummoned(popLoiteringEnemyPosition, 5);
			new FloatParticleEffect(Vector3(30,0,0)+ popLoiteringEnemyPosition, Vector3(0, 2, 0));
			new FloatParticleEffect(Vector3(-30,0,0)+ popLoiteringEnemyPosition, Vector3(0, 2, 0));
			mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -350), meleeEnemy->GetPosition());
			directingCount++;
		}
		else if (directingCount >= 600)//530
		{
			//meleeEnemy->SetPosition(popLoiteringEnemyPosition);
			pauzingEvent = PauzingEvent::NoneEvent;
			actionName = MageActionName::FloatShot;
			animComponent->SetSubDuration(0.017f);
		}
		else
		{
			directingCount++;
		}
	}
}

/*
@brief 待機状態から戦闘状態に入る関数　初期化に
*/
void MageEnemy::SetAttackState(GameObject* _playerObject)
{
	playerObject = _playerObject;
	attackState = true;
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 50, -400), position);
	animComponent->SetSpawn(true);
}

/*
@fn 状態(MageActionName)ごとのアクションを行う
*/
void MageEnemy::UpdateEnemyObject(float _deltaTime)
{
	//プレイヤーが射程距離内に入り攻撃態勢に入っているか
	if (attackState)
	{
		if (playerObject == nullptr)
		{
			return;
		}
		//追跡対象の座標を取得
		Vector3 target = playerObject->GetPosition();
		//プレイヤーとのx座標間の距離を計算
		float playerDistance = position.x - target.x;

		switch (actionName)
		{
		case(MageActionName::FloatShot):
			//プレイヤーの位置で向きを変更
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
				meleeEnemy->SpawnSummoned(popLoiteringEnemyPosition + Vector3(100, 0, 0), 5);
				new FloatParticleEffect(Vector3(30, 0, 0) + popLoiteringEnemyPosition + Vector3(100, 0, 0), Vector3(0,2,0));
				new FloatParticleEffect(Vector3(-30, 0, 0) + popLoiteringEnemyPosition + Vector3(100, 0, 0), Vector3(0,2,0));
				rangeEnemy->SpawnSummoned(popLoiteringEnemyPosition + Vector3(-100, 0, 0), 5);
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
@fn 召喚した敵が生存しているか。していないときスタンする。
*/
void MageEnemy::AliveLoiteringEnemyCheck()
{
	if ((meleeEnemy->GetState() == State::Dead&&rangeEnemy->GetState() == State::Dead) && attackState)
	{
		subActionClass->StartDroppingDown();
		barrier = false;
		actionName = MageActionName::Stanning;
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
@fn 撃破イベント
*/
void MageEnemy::DeadEvent()
{
	goalWallObject->SetState(State::Dead);
}

/*
@fn 攻撃されたとき。召喚した敵が生存しているとき攻撃を喰らわない
*/
void MageEnemy::HitPlayerAttack(const Vector3& _pairPos,const int& _power)
{
	if (!barrier)
	{
		hitPoint-=_power;
	}
	else
	{
		printf("Mages Guard HitPoint : %d \n",hitPoint);
	}
}

/*
@fn プレイヤーに向けて弾を発射する
@param _target 目標座標
*/
void MageEnemy::Shot(const Vector3& target)
{
	if (shotInterval <= 0)
	{
		shotInterval = ShotInterval;
		attackObject=new StraightMagicBullet(position, target, 100);
		animComponent->SetAttack(true);
	}
	else
	{
		animComponent->SetAttack(false);
		shotInterval--;
	}
}
