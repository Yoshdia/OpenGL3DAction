#include "EnemyBase.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ColliderComponent.h"
#include "SkeltonObjectChecker.h"

const float EnemyBase::NockBackPower = 30;
const float EnemyBase::GroundCheckPos = 40;
const int EnemyBase::DefaultActionChangeCountMax = 500;
const Vector3 EnemyBase::footPos = Vector3(0, -25, 0);
const float EnemyBase::ForwardDownY = -90;
const float EnemyBase::SearchRange = 200;
const float EnemyBase::Gravity = -5;
const float EnemyBase::WalkSpeed = 2;
const int EnemyBase::TurnWaitCountMax = 5;
const float EnemyBase::ApproachSpeedRatio = 0.8f;

EnemyBase::EnemyBase(const std::string& meshName) :
	GameObject(),
	actionChangeCount(0),
	defaultActionChangeCountMax(DefaultActionChangeCountMax),
	actionChangeCountMax(DefaultActionChangeCountMax),
	moveDirection(EnemyMoveDirection::right),
	actionName(EnemyActions::walk),
	turnWaitCount(0),
	nockBackForce(Vector3::Zero),
	attackRange(75)
{
	tag = Tag::EnemyTag;
	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh(meshName));

	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker= new SkeltonObjectChecker(this,footPos, Vector3(1, 1, 1), Tag::GroundTag);

	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos*moveDirection, ForwardDownY, 0),Vector3(1,1,1),Tag::GroundTag);
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos*moveDirection, 0, 0), Vector3(1, 1, 1), Tag::GroundTag);
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(SearchRange/2, 1, 0), Vector3(SearchRange, 1, 1), Tag::PlayerTag);
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
	ActionChange();
	Action(_deltaTime);

	//攻撃対象を発見したときにアクションを変更する
	if (!findingPlayerCheck->GetNoTouchingFlag())
	{
		actionName = EnemyActions::approach;
	}
	//移動方向に変更が加わった際にすぐそっちを見るように座標を更新し続ける
	findingPlayerCheck->SetOffset(Vector3((SearchRange/2) * moveDirection, 0, 0));
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
	//プレイヤーとの距離を計算
	float playerDistance = Math::Abs(position.x - findingPlayerCheck->GetColliderPairPosition().x);
	switch (actionName)
	{
	case(EnemyActions::walk):
		//歩行
		SetPosition(Vector3(WalkSpeed * moveDirection, 0, 0) + position);
		//現在空中にいないか
		if (!footChecker->GetNoTouchingFlag())
		{
			//進行方向に壁があるか||進行方向の足元に地面が無いか
			if (forwardDownGroundCheck->GetNoTouchingFlag()|| !forwardGroundCheck->GetNoTouchingFlag())
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
		break;
	case(EnemyActions::noActive):
		//何もしない
		break;
	case(EnemyActions::approach):
		//攻撃対象に接近する
		SetPosition(Vector3::Lerp(position, findingPlayerCheck->GetColliderPairPosition(), _deltaTime * ApproachSpeedRatio));
		//攻撃の射程距離まで接近したらアクションを変更する
		if (playerDistance < attackRange)
		{
			actionName = EnemyActions::attack;
		}
		break;
	case(EnemyActions::attack):
		//攻撃の射程距離から離れたらアクションを変更する
		if (playerDistance >= attackRange)
		{
			actionName = EnemyActions::approach;
		}
		break;
	}
}

void EnemyBase::BranchActionChange()
{
	//攻撃中又は攻撃対象に接近中はアクションを変更しない
	if (actionName == EnemyActions::attack || actionName == EnemyActions::approach)
	{
		return;
	}
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
	moveDirection = EnemyMoveDirection(rand() % 3);
}

void EnemyBase::ShuffleCountMax()
{
	//次のアクション変更時間をデフォルト+乱数で決定
	actionChangeCountMax = defaultActionChangeCountMax + ((rand() % 10) * 100);
}
