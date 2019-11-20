#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "SkeltonObjectChecker.h"

const float EnemyBase::NockBackPower = 30;
const float EnemyBase::GroundCheckPos = 40;
const int EnemyBase::DefaultActionChangeCountMax = 200;
const Vector3 EnemyBase::footPos = Vector3(0, -25, 0);
const Vector3 EnemyBase::TrackingRange = Vector3(1000, 1000, 1000);
const float EnemyBase::ForwardDownY = -90;
const float EnemyBase::SearchRange = 200;
const float EnemyBase::Gravity = -10;
const float EnemyBase::WalkSpeed = 2;
const int EnemyBase::TurnWaitCountMax = 5;
const float EnemyBase::ApproachSpeedRatio = 0.8f;
const float EnemyBase::AttackRange = 75.0f;

EnemyBase::EnemyBase(const std::string& meshName) :
	GameObject(),
	actionChangeCount(0),
	defaultActionChangeCountMax(DefaultActionChangeCountMax),
	actionChangeCountMax(DefaultActionChangeCountMax),
	moveDirection(EnemyMoveDirection::right),
	actionName(EnemyActions::walk),
	turnWaitCount(0),
	nockBackForce(Vector3::Zero),
	attackRange(AttackRange),
	attackingState(false),
	teleportChargingTime(0)
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));

	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(1, 1, 1), Tag::GroundTag);

	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(1, 1, 1), Tag::GroundTag);
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(SearchRange, 1, 0), Vector3(SearchRange, 1, 1), Tag::PlayerTag);
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::UpdateGameObject(float _deltaTime)
{
	//地面と接触していないとき重力を働かせる
	if (footChecker->GetNoTouchingFlag())
	{
		SetPosition(position + Vector3(0, Gravity, 0));
	}
	UpdateEnemyObject(_deltaTime);
	NockBack();
	Action(_deltaTime);

	//移動方向に変更が加わった際にすぐそっちを見るように座標を更新し続ける
	findingPlayerCheck->SetOffset(Vector3((SearchRange)*moveDirection, 0, 0));
}

void EnemyBase::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		//printf("\nouti!"); 
	}
}

void EnemyBase::OnTriggerEnter(ColliderComponent* colliderPair)
{
	//プレイヤーの攻撃に接触したとき
	if (colliderPair->GetObjectTag() == Tag::PlayerWeaponTag)
	{
		//プレイヤーの攻撃の方向を計算しnockBackForceに計算
		double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
		Vector3 force = Vector3::Normalize(Vector3((position.x - colliderPair->GetPosition().x), (position.y - colliderPair->GetPosition().y), (position.z - colliderPair->GetPosition().z)));
		nockBackForce = force * NockBackPower;
	}
}

void EnemyBase::NockBack()
{
	//nockBackForceの最小数を設定
	if (nockBackForce.x >= 0.1f && nockBackForce.x <= -0.1f)
	{
		nockBackForce = Vector3::Zero;
		return;
	}

	SetPosition(position + nockBackForce);
	//nockBackForceを半減
	nockBackForce = nockBackForce / 2.0f;
}

void EnemyBase::ActionChange()
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

void EnemyBase::Action(float _deltaTime)
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

void EnemyBase::BranchActionChange()
{
	//棒立ち、歩行を設定する乱数
	int ra = rand() % 4;
	if (ra <= 4)
	{
		actionName = EnemyActions::walk;
	}
	else
	{
		actionName = EnemyActions::noActive;
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
}

void EnemyBase::ShuffleCountMax()
{
	//次のアクション変更時間をデフォルト+乱数で決定
	actionChangeCountMax = defaultActionChangeCountMax + ((rand() % 10) * 100);
}

void EnemyBase::NoAttacking(float _deltaTime)
{
	if (actionName == EnemyActions::walk)
	{
		//歩行
		SetPosition(Vector3(WalkSpeed * moveDirection, 0, 0) + position);
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
	}
	else
	{
		//何もしない
	}
	//攻撃対象を発見したときにアクションを変更する
	if (!findingPlayerCheck->GetNoTouchingFlag())
	{
		actionName = EnemyActions::approach;
		attackingState = true;
	}
}

void EnemyBase::Attacking(float _deltaTime)
{
	//追跡対象の座標を取得
	Vector3 target = trackingRange->GetColliderPairPosition();
	//プレイヤーとの距離を計算
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
	//向きが反転することがあるためそれぞれのoffset座標を更新する
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//絶対値に変換
	playerDistance = Math::Abs(playerDistance);

	if (actionName == EnemyActions::approach)
	{
		//追跡対象と高さの差が10以上ある状態でカウントが100進むと追跡対象から一定以上離れた位置にテレポート
		float heightDistance = Math::Abs(position.y - target.y);
		if (heightDistance > 10&& playerDistance>100)
		{
			teleportChargingTime++;
		}
		else
		{
			teleportChargingTime = 0;
		}
		if (teleportChargingTime > 100)
		{
			teleportChargingTime = 0;
			Vector3 teleportPosition = target;
			teleportPosition.x += (100 * moveDirection) * -1;
			SetPosition(teleportPosition);
		}
		//進行方向に壁があるか||進行方向の足元に地面が無いか
		if (!forwardDownGroundCheck->GetNoTouchingFlag() && forwardGroundCheck->GetNoTouchingFlag())
		{
			//攻撃対象に接近する 浮遊はできないためy方向には追跡しない
			SetPosition(Vector3::Lerp(position, Vector3(target.x, position.y, target.z), _deltaTime * ApproachSpeedRatio));


			//攻撃の射程距離まで接近したらアクションを変更する
			if (playerDistance < attackRange)
			{
				actionName = EnemyActions::attack;
			}
		}
	}
	else
	{
		//攻撃の射程距離から離れたらアクションを変更する
		if (playerDistance >= attackRange)
		{
			actionName = EnemyActions::approach;
		}
	}
}
