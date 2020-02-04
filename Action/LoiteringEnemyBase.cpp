#include "LoiteringEnemyBase.h"
#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"

const int LoiteringEnemyBase::HitPointMax = 3;
const int LoiteringEnemyBase::AttackingTime = 200;
const int LoiteringEnemyBase::HittingTime = 40;
const float LoiteringEnemyBase::WalkSpeed = 125;
const float LoiteringEnemyBase::ApproachSpeedRatio = 0.8f;
const float LoiteringEnemyBase::SearchRange = 200;
const float LoiteringEnemyBase::AttackRange = 75;
const int LoiteringEnemyBase::AttackIntervalCount = 20;

const float LoiteringEnemyBase::Gravity = 550.0f;
const float LoiteringEnemyBase::NockBackPower = 1075.0f;
const float LoiteringEnemyBase::GroundCheckPos = 40;
const int LoiteringEnemyBase::ActionChangeCountMax = 100;
const Vector3 LoiteringEnemyBase::footPos = Vector3(0, -3, 0);
const Vector3 LoiteringEnemyBase::TrackingRange = Vector3(2000, 2000, 2000);
const int LoiteringEnemyBase::TurnWaitCountMax = 2;
const float LoiteringEnemyBase::ForwardDownY = -90;

LoiteringEnemyBase::LoiteringEnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	EnemyBase(_pos, _scale, _type),
	actionChangeCount(0),
	attackingTime(AttackingTime),
	hittingTime(HittingTime),
	walkSpeed(WalkSpeed),
	approachSpeedRatio(ApproachSpeedRatio),
	searchRange(SearchRange),
	attackIntervalCountMax(AttackIntervalCount),
	attackRange(AttackRange),
	actionName(EnemyActions::walk),
	turnWaitCount(0),
	nockBackForce(Vector3::Zero),
	attackingState(false),
	teleportChargingTime(0),
	attackIntervalCount(0),
	canNotActionTime(0),
	actionChangeCountMax(ActionChangeCountMax),
	warpPositonSearching(false)
{
	hitPoint = HitPointMax;

	warpSearch = new WarpPointSearchEnemy();
	//InstantiateLoiteringEnemyBaseを派生クラスコンストラクタ内で呼ぶこと
}

void LoiteringEnemyBase::InstantiateLoiteringEnemyBase()
{
	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(10, 10, 10), Tag::GroundTag);
	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(10, 10, 10), Tag::GroundTag);
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, -20, 0), Vector3(10, 10, 10), Tag::GroundTag);
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(searchRange / 1.5f, 5, 0), Vector3(searchRange, 15, 1), Tag::PlayerTag);
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);
}

LoiteringEnemyBase::~LoiteringEnemyBase()
{
}

void LoiteringEnemyBase::SpawnSummoned(const Vector3& _pos, const int& _hitPoint)
{
	SetPosition(_pos);
	trackingRange->SetPosition(_pos);
	trackingRange->SetState(State::Active);
	footChecker->SetPosition(_pos);
	footChecker->SetState(State::Active);
	forwardDownGroundCheck->SetPosition(_pos);
	forwardDownGroundCheck->SetState(State::Active);
	forwardGroundCheck->SetPosition(_pos);
	forwardGroundCheck->SetState(State::Active);
	findingPlayerCheck->SetPosition(_pos);
	findingPlayerCheck->SetState(State::Active);

	hitPoint = _hitPoint;
	canNotActionTime = 200;
	SetState(State::Active);
	animComponent->AllFlagReset();
	animComponent->SetSpawn(true);
	animComponent->SetSubDuration(0.01f);
	actionName = EnemyActions::approach;
	attackingState = true;
	if (moveDirection == EnemyMoveDirection::right)
	{
		moveDirection = EnemyMoveDirection::left;
		beforeDirection = moveDirection;
		rotate->SetRotation(180, Vector3::UnitY);

	}
}

void LoiteringEnemyBase::UpdateEnemyObject(float _deltaTime)
{
	//地面と接触していないとき重力を働かせる
	if (footChecker->GetNoTouchingFlag())
	{
		SetPosition(position + Vector3(0, -Gravity * _deltaTime, 0));
	}
	//ノックバック
	NockBack(_deltaTime);
	//徘徊や攻撃などのアクション
	Action(_deltaTime);
	UpdateLoiteringEnemyObject(_deltaTime);
}

void LoiteringEnemyBase::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void LoiteringEnemyBase::PausingUpdateGameObject()
{
	//animComponent->UpdateAnimationComponent(0.6f);
}

void LoiteringEnemyBase::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	hitPoint -= _power;
	if (!attackingState)
	{
		attackingState = true;
		actionName = EnemyActions::approach;
	}
	//プレイヤーの攻撃の方向を計算しnockBackForceに計算
	double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
	Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
	nockBackForce = force * NockBackPower;
	canNotActionTime = hittingTime;
}

void LoiteringEnemyBase::DeadEvent()
{
}

void LoiteringEnemyBase::NockBack(float _deltaTime)
{
	//nockBackForceの最小数を設定
	if (nockBackForce.x <= 0.1f && nockBackForce.x >= -0.1f)
	{
		nockBackForce = Vector3::Zero;
		return;
	}
	SetPosition(position + (nockBackForce*_deltaTime));
	//nockBackForceを半減
	nockBackForce = nockBackForce / 2.0f;
}

void LoiteringEnemyBase::ActionChange()
{
	if (actionChangeCount > actionChangeCountMax)
	{
		actionChangeCount = 0;
		BranchActionChange();
		ShuffleCountMax();
	}
	else
	{
		actionChangeCount++;
	}
}

void LoiteringEnemyBase::Action(float _deltaTime)
{
	if (canNotActionTime <= 0)
	{
		if (attackingState)
		{
			Attacking(_deltaTime);
		}
		else
		{
			NoAttacking(_deltaTime);
			ActionChange();
		}
	}
	else
	{
		animComponent->SetAttack(false);
		canNotActionTime--;
	}
	attackIntervalCount--;
}

void LoiteringEnemyBase::BranchActionChange()
{
	//棒立ち、歩行を設定する乱数
	int ra = rand() % 6;
	if (ra <= 1)
	{
		actionName = EnemyActions::walk;
		animComponent->SetMove(true);
	}
	else
	{
		actionName = EnemyActions::noActive;
		animComponent->SetMove(false);

	}
	//向きをランダムで決定
	if ((rand() % 100) < 50)
	{
		moveDirection = EnemyMoveDirection::left;
	}
	else
	{
		moveDirection = EnemyMoveDirection::right;
	}
	//移動方向に変更が加わった際にすぐそっちを見るように座標を更新し続ける
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	findingPlayerCheck->SetOffset(Vector3((searchRange)*moveDirection, 0, 0));
}

void LoiteringEnemyBase::ShuffleCountMax()
{
}

void LoiteringEnemyBase::Attacking(float _deltaTime)
{
	//追跡対象の座標を取得
	Vector3 target = trackingRange->GetColliderPairPosition();
	//プレイヤーとのx座標間の距離を計算
	float playerDistance = position.x - target.x;
	//プレイヤーの位置で向きを変更
	if (playerDistance >= 0)
	{
		moveDirection = EnemyMoveDirection::left;
	}
	else
	{
		moveDirection = EnemyMoveDirection::right;
	}
	float heightDistance = Math::Abs(position.y - target.y);
	//向きが反転することがあるためそれぞれのoffset座標を更新する
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//絶対値に変換
	playerDistance = Math::Abs(playerDistance);

	if (actionName == EnemyActions::approach)
	{
		//追跡対象と高さの差が10以上ある状態でカウントが100進むと追跡対象から一定以上離れた位置にテレポート

		if ((heightDistance > 25 || playerDistance > attackRange * 10) && !warpPositonSearching)
		{
			teleportChargingTime++;
		}
		else
		{
			teleportChargingTime = 0;
		}
		if (teleportChargingTime > 100 && !warpPositonSearching)
		{
			teleportChargingTime = 0;
			//ワープ地点指定の開始
			warpSearch->SetFirstPosition(target, position);
			warpPositonSearching = true;
		}
		if (warpPositonSearching)
		{
			//ワープ地点指定が終了したら
			if (warpSearch->GetEndSearch())
			{
				//ワープ地点にワープ
				SetPosition(warpSearch->GetPosition());
				warpPositonSearching = false;
				teleportChargingTime = 0;
			}
		}
		//進行方向に壁があるか||進行方向の足元に地面が無いか
		if (!forwardDownGroundCheck->GetNoTouchingFlag() && !forwardGroundCheck->GetNoTouchingFlag())
		{
			//攻撃対象に接近する 浮遊はできないためy方向には追跡しない
			SetPosition(Vector3::Lerp(position, Vector3(target.x, position.y, target.z), _deltaTime * approachSpeedRatio));

			animComponent->SetMove(true);
		}
		else
		{
			//forwardDownGroundCheck->SetPosition(Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0) + position);
			//forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0));
			//forwardGroundCheck->SetPosition(Vector3(GroundCheckPos * moveDirection, 0, 0) + position);
			//forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));

			animComponent->SetMove(false);
		}
		//攻撃の射程距離まで接近したらアクションを変更する
		if (playerDistance < attackRange)
		{
			actionName = EnemyActions::attack;
			animComponent->SetMove(false);
		}
	}
	else
	{
		warpPositonSearching = false;
		//攻撃の射程距離から離れたらアクションを変更する
		if (playerDistance >= attackRange || heightDistance > 25)
		{
			actionName = EnemyActions::approach;

			animComponent->SetAttack(false);
			if (teleportChargingTime <= 0)
			{
				animComponent->SetMove(true);
			}
			//animComponent->SetSubDuration(0.02f);
		}
		else if (attackIntervalCount <= 0)
		{
			attackIntervalCount = attackIntervalCountMax;
			animComponent->SetAttack(true);
			animComponent->SetSubDuration(0.016f);
			animComponent->SetMove(false);
			canNotActionTime = attackingTime;
			Attack(_deltaTime);
		}
		else
		{
			animComponent->SetAttack(false);
		}
	}
}

void LoiteringEnemyBase::Attack(float _deltaTime)
{

}

void LoiteringEnemyBase::NoAttacking(float _deltaTime)
{
	if (actionName == EnemyActions::walk)
	{
		//現在空中にいないか
		if (!footChecker->GetNoTouchingFlag())
		{
			//進行方向に壁があるか||進行方向の足元に地面が無いか
			if (forwardDownGroundCheck->GetNoTouchingFlag() || !forwardGroundCheck->GetNoTouchingFlag())
			{
				if (turnWaitCount > TurnWaitCountMax)
				{
					turnWaitCount = 0;
					//移動方向を反転
					moveDirection = (EnemyMoveDirection)(moveDirection * (EnemyMoveDirection)-1);
					//移動方向が反転したのでそれぞれのoffset座標を更新する
					forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
					forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
				}
			}
			else
			{
				turnWaitCount++;
			}
		}
		//歩行
		SetPosition(Vector3((walkSpeed * _deltaTime) * moveDirection, 0, 0) + position);
	}
	else
	{
		SetPosition(position);
		//何もしない
	}
	//攻撃対象を発見したときにアクションを変更する
	if (!findingPlayerCheck->GetNoTouchingFlag())
	{
		actionName = EnemyActions::approach;
		attackingState = true;
		animComponent->SetMove(true);
	}
}
