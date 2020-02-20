#include "LoiteringEnemyBase.h"
#include "WarpPointSearchEnemy.h"
#include "SkeltonObjectChecker.h"
#include "RotateComponent.h"
#include "AnimationEnemyComponent.h"
#include "EnemyWeapon.h"
#include "FloatParticleEffect.h"

const int LoiteringEnemyBase::HitPointMaxDefault = 3;
const int LoiteringEnemyBase::AttackingTimeDefault = 200;
const int LoiteringEnemyBase::HittingTimeDefault = 40;
const float LoiteringEnemyBase::WalkSpeedDefault = 125;
const float LoiteringEnemyBase::ApproachSpeedRatioDefault = 0.8f;
const float LoiteringEnemyBase::SearchRangeDefault = 200;
const float LoiteringEnemyBase::AttackRangeDefault = 75;
const int LoiteringEnemyBase::AttackIntervalCountDefault = 20;

const float LoiteringEnemyBase::Gravity = 550.0f;
const float LoiteringEnemyBase::NockBackPower = 1075.0f;
const float LoiteringEnemyBase::GroundCheckPos = 40.0f;
const int LoiteringEnemyBase::ActionChangeCountMax = 100;
const Vector3 LoiteringEnemyBase::footPos = Vector3(0.0f, -3.0f, 0.0f);
const Vector3 LoiteringEnemyBase::TrackingRange = Vector3(2000.0f, 2000.0f, 2000.0f);
const int LoiteringEnemyBase::TurnWaitCountMax = 2;
const float LoiteringEnemyBase::ForwardDownY = -90.0f;

/*
@param _pos 座標
@param _scale サイズ
@param _type エネミーの種類
@sa　引数はすべてEnemyBaseに渡す
*/
LoiteringEnemyBase::LoiteringEnemyBase(Vector3 _pos, Vector3 _scale, EnemyType _type) :
	EnemyBase(_pos, _scale, _type),
	actionChangeCount(0),
	attackingTime(AttackingTimeDefault),
	hittingTime(HittingTimeDefault),
	walkSpeed(WalkSpeedDefault),
	approachSpeedRatio(ApproachSpeedRatioDefault),
	searchRange(SearchRangeDefault),
	attackRange(AttackRangeDefault),
	attackIntervalCountMax(AttackIntervalCountDefault),
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
	hitPoint = HitPointMaxDefault;

	warpSearch = new WarpPointSearchEnemy();
	//InstantiateLoiteringEnemyBaseを派生クラスコンストラクタ内で呼ぶこと
}

/*
@fn 初期化関数
@brief 派生クラスごとに変更が行われた定数を別クラスに反映させるために別個に用意
*/
void LoiteringEnemyBase::InstantiateLoiteringEnemyBase()
{
	//足元の地面判別
	footChecker = new SkeltonObjectChecker(this, footPos, Vector3(10, 10, 10), Tag::GroundTag);
	//進行方向足元の地面判別
	forwardDownGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, ForwardDownY, 0), Vector3(10, 10, 10), Tag::GroundTag);
	//進行方向の壁を判別
	forwardGroundCheck = new SkeltonObjectChecker(this, Vector3(GroundCheckPos * moveDirection, -20, 0), Vector3(10, 10, 10), Tag::GroundTag);
	//プレイヤーを探す、索敵範囲
	findingPlayerCheck = new SkeltonObjectChecker(this, Vector3(searchRange / 1.5f, 5, 0), Vector3(searchRange, 15, 1), Tag::PlayerTag);
	//プレイヤーを発見後、追跡するためにプレイヤーの座標を更新する
	trackingRange = new SkeltonObjectChecker(this, Vector3::Zero, TrackingRange, Tag::PlayerTag);
}

LoiteringEnemyBase::~LoiteringEnemyBase()
{
}

/*
@fn このオブジェクトが使いまわしされるときに呼ばれ、パラメータを初期化する
@param _pos 座標
@param _hitPoint 体力
@brief 主にMageEnemyに召喚されるように使用される
@sa MageEnemy.h
*/
void LoiteringEnemyBase::SpawnSummoned(const Vector3& _pos, const int& _hitPoint)
{
	//引数の座標をセット
	SetPosition(_pos);
	//更新状態をアクティブに
	SetState(State::Active);
	//各サブクラスの座標をセットし全てアクティブに
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

	//引数の体力をセット
	hitPoint = _hitPoint;
	//行動不可時間を追加
	canNotActionTime = 200;
	//アニメーションクラスのフラグをリセット
	animComponent->AllFlagReset();
	//湧きアニメーション
	animComponent->SetSpawn(true);
	//湧きアニメーションの速度をセット
	animComponent->SetSubDuration(0.01f);
	//活動状態を追跡に
	actionName = EnemyActions::approach;
	//攻撃状態をアクティブに
	attackingState = true;
	//変数上の向きと角度上の向きを合わせる(右を向きながら左に進行することがあったため)
	if (moveDirection == EnemyMoveDirection::right)
	{
		moveDirection = EnemyMoveDirection::left;
		beforeDirection = moveDirection;
		rotate->SetRotation(180, Vector3::UnitY);
	}
}

/*
@fn この徘徊エネミー共通の更新関数
*/
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
	//派生クラスの更新関数
	UpdateLoiteringEnemyObject(_deltaTime);
}

/*
@fn 派生クラスの更新関数
*/
void LoiteringEnemyBase::UpdateLoiteringEnemyObject(float _deltaTime)
{
}

void LoiteringEnemyBase::PausingUpdateGameObject()
{
}

/*
@fn プレイヤーに攻撃された
@brief 体力を減らし、非攻撃態勢だった場合攻撃態勢に移行、ノックバックし被弾中はアクション出来なくなる
@param _pairPos 衝突相手の座標
@param _power ダメージ
*/
void LoiteringEnemyBase::HitPlayerAttack(const Vector3& _pairPos, const int& _power)
{
	//被弾時の発光を開始
	animComponent->SetStartFlash();
	//引数で受け取った武器の威力で体力を減らす
	hitPoint -= _power;
	//攻撃状態でないときに被弾した場合プレイヤーを発見した状態になる
	if (!attackingState)
	{
		attackingState = true;
		actionName = EnemyActions::approach;
	}
	//プレイヤーの攻撃の方向を計算しnockBackForceに計算
	double distance = Math::Sqrt((_pairPos.x - position.x) * (_pairPos.x - position.x) + (_pairPos.y - position.y) * (_pairPos.y - position.y));
	//distanceを元にノックバックする方向を正規化
	Vector3 force = Vector3::Normalize(Vector3((position.x - _pairPos.x), 0, (position.z - _pairPos.z)));
	//ノックバック力を計算
	nockBackForce = force * NockBackPower;
	//硬直中でない場合被弾時の硬直を付与(大量の硬直を得ているときに被弾すると即行動できてしまうため
	if (canNotActionTime < hittingTime)
	{
		canNotActionTime = hittingTime;
	}
}

/*
@fn 撃破イベント
*/
void LoiteringEnemyBase::DeadEvent()
{
}

/*
@fn ノックバック
*/
void LoiteringEnemyBase::NockBack(float _deltaTime)
{
	//nockBackForceの最小数を設定
	if (nockBackForce.x <= 0.1f && nockBackForce.x >= -0.1f)
	{
		nockBackForce = Vector3::Zero;
		return;
	}
	//ノックバック
	SetPosition(position + (nockBackForce * _deltaTime));
	//nockBackForceを半減
	nockBackForce = nockBackForce / 2.0f;
}

/*
@fn アクション変更
*/
void LoiteringEnemyBase::ActionChange()
{
	//アクション変更の待機時間カウント
	if (actionChangeCount > actionChangeCountMax)
	{
		actionChangeCount = 0;
		//アクション変更
		BranchActionChange();
	}
	else
	{
		actionChangeCount++;
	}
}

/*
@fnアクションごとの処理
*/
void LoiteringEnemyBase::Action(float _deltaTime)
{
	//硬直中でないか
	if (canNotActionTime <= 0)
	{
		//攻撃状態であるか
		if (attackingState)
		{
			Attacking(_deltaTime);
		}
		else
		{
			NoAttacking(_deltaTime);
			//非攻撃状態のため、行動をランダムで変更する
			ActionChange();
		}
	}
	else
	{
		//硬直があるときに棒立ちさせるため最も建つ攻撃フラグをリセット
		animComponent->SetAttack(false);
		//硬直カウントをリセット
		canNotActionTime--;
	}
	//攻撃インターバルを減少
	attackIntervalCount--;
}

/*
@fn 実行中アクションが変更される関数
*/
void LoiteringEnemyBase::BranchActionChange()
{
	//棒立ち、歩行を設定する乱数
	int ra = rand() % 6;
	if (ra <= 1)
	{
		//徘徊
		actionName = EnemyActions::walk;
		animComponent->SetMove(true);
	}
	else
	{
		//棒立ち
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
	//移動方向に変更が加わった際にすぐそちらを見るように座標を更新し続ける
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	findingPlayerCheck->SetOffset(Vector3((searchRange)*moveDirection, 0, 0));
}

/*
@fn 攻撃態勢の処理
*/
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
	//標的との高さの差を計算
	float heightDistance = Math::Abs(position.y - target.y);
	//向きが反転することがあるためそれぞれのoffset座標を更新する
	forwardDownGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, -90, 0));
	forwardGroundCheck->SetOffset(Vector3(GroundCheckPos * moveDirection, 0, 0));
	//絶対値に変換
	playerDistance = Math::Abs(playerDistance);
	//標的に接近中
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
		//座標を検索中でなくカウントが一定以上になったとき
		if (teleportChargingTime > 100 && !warpPositonSearching)
		{
			teleportChargingTime = 0;
			//ワープ地点指定の開始
			warpSearch->SetFirstPosition(target, position);
			warpPositonSearching = true;
		}
		//座標を検索中
		if (warpPositonSearching)
		{
			//ワープ地点指定が終了したら
			if (warpSearch->GetEndSearch())
			{
				//ワープエフェクト
				new FloatParticleEffect(Vector3(45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(45, 0, 0) + position, Vector3(0, 2, 0));
				new FloatParticleEffect(Vector3(-45, 0, 0) + position, Vector3(0, 2, 0));
				//検索地点にワープ
				SetPosition(warpSearch->GetPosition());
				//ワープ後即攻撃できないよう硬直を追加
				canNotActionTime = 50;
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
			//徘徊
			actionName = EnemyActions::approach;
			animComponent->SetAttack(false);
			if (teleportChargingTime <= 0)
			{
				animComponent->SetMove(true);
			}
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

/*
@fn 攻撃を行う関数
@sa EnemyWeapon.h
*/
void LoiteringEnemyBase::Attack(float _deltaTime)
{

}
/*
@fn 非攻撃態勢
*/
void LoiteringEnemyBase::NoAttacking(float _deltaTime)
{
	if (actionName == EnemyActions::walk)
	{
		//現在空中にいないか
		if (!footChecker->GetNoTouchingFlag())
		{
			//進行方向に壁があるか||進行方向の足元に地面が無いか
			if (!forwardDownGroundCheck->GetNoTouchingFlag() && !forwardGroundCheck->GetNoTouchingFlag())
			{
				turnWaitCount++;
			}
			else
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
