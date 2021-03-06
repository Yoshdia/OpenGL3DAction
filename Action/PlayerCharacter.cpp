#include "PlayerCharacter.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "InputSystem.h"
#include "AttackPlayerObject.h"
#include "ColliderComponent.h"
#include "SkeltonObjectChecker.h"
#include "GuardPlayerComponent.h"
#include "ParticleComponent.h"
#include "Game.h"
#include "PhysicsWorld.h"
#include "MainCameraObject.h"
#include "GameObjectManager.h"
#include "HeartParticleEffect.h"
#include "UserInterfaceBase.h"
#include "HaveLifeCountUI.h"

const float PlayerCharacter::MoveSpeed = 450;
const float PlayerCharacter::GravityPower = 0.7f;
const float PlayerCharacter::JumpPower = 13.0f;
const float PlayerCharacter::MoveFriction = 1.2f;
const float PlayerCharacter::DownFriction = 1.05f;

const int PlayerCharacter::InvincibleCount = 20;
const int PlayerCharacter::InputUnderCountMax = 20;
const int PlayerCharacter::AvoidanceInterval = 40;
const int PlayerCharacter::AvoidanceInvincible = 30;
const int PlayerCharacter::CandleHealingInterval = 200;
const int PlayerCharacter::HitPointMax = 5;

const Vector3 PlayerCharacter::HitPointUIPos = Vector3(-750, -400, 0);
const float PlayerCharacter::HitPointUIWidth = 50.0f;
const float PlayerCharacter::HitPointUISize = 0.6f;

/*
	@param _pos 座標
	*/
PlayerCharacter::PlayerCharacter(const Vector3& _pos) :
	GameObject(),
	inputDirection(0),
	canNotActionTime(0),
	velocity(Vector3(0, 0, 0)),
	attackBottonInput(false),
	jumpBottonInput(false),
	rangeAttackBottonInput(false),
	avoidanceBottonInput(false),
	direction(1.0f),
	invincible(false),
	invincibleCount(0),
	isFloating(false),
	isThinGroundCollision(false),
	noInputForUnderDirection(false),
	doSkeletonThinGround(false),
	isLive(true),
	hitPoint(HitPointMax),
	avoidancing(false),
	avoidanceInterval(0),
	candleHealingInterval(0),
	inputUnderCount(0),
	inputUnderDirection(0),
	doubleJump(false),
	doubleJumpInterval(0)
{
	tag = Tag::PlayerTag;
	SetPosition(_pos);
	//スケールを設定
	float scaleF = 60.0f;
	SetScale(60.0f);

	animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerObject(this);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, Vector3(0, -30, 0), Vector3(20, 1, 20), Tag::GroundTag);
	thinChecker = new SkeltonObjectChecker(this, Vector3(0, -30, 0), Vector3(20, 1, 20), Tag::ThinGroundFloor);
	headRoofChecker = new SkeltonObjectChecker(this, Vector3(0, 30, 0), Vector3(20, 1, 20), Tag::GroundTag);

	//Hpの数まで体力UIを生成する
	for (int num = 0; num < HitPointMax; num++)
	{
		new UserInterfaceBase(HitPointUIPos + Vector3(HitPointUIWidth * num, 0, 0), "Assets/Image/UI/HpCase.png", Vector3(HitPointUISize, HitPointUISize, HitPointUISize), 1000);
	}
	mainCamera->SetPosition(position + Vector3(0, 0, -300));
}

PlayerCharacter::~PlayerCharacter()
{
}

/*
@fn アクション状態ごとにアクションを行う
*/
void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	isThinGroundCollision = false;
	//カメラの追跡先をセット 
	mainCamera->SetViewMatrixLerpObject(Vector3(0, 0, -500), position);
	//着地状態
	bool noGround = footChecker->GetNoTouchingFlag() && (thinChecker->GetNoTouchingFlag());

	//着地状態のとき上下方向への力をリセットする
	if ((!noGround && !isFloating) || !headRoofChecker->GetNoTouchingFlag())  
	{
		velocity.y = 0;
	}
	//入力によるアクションができるか
	if (canNotActionTime < 0 && !invincible)
	{
		Actions(_deltaTime, noGround);
	}
	else
	{
		canNotActionTime--;
	}
	//空中なら重力を付与
	if (noGround || (doSkeletonThinGround))
	{
		Gravity(_deltaTime);
		//ダブルジャンプへの待機カウントが一定値を超えたら
		if (doubleJumpInterval >= 20)
		{
			//入力があったらダブルジャンプする
			if (jumpBottonInput && !doubleJump)
			{
				Jump();
				doubleJump = true;
			}
		}
		else
		{
			doubleJumpInterval++;
		}
		//下方向への入力
		if (inputUnderDirection > 0)
		{
			doSkeletonThinGround = true;
		}
		//落下中か
		if (velocity.y < 0)
		{
			//地面と接触していないなら落下アニメーションへ
			if (noGround)
			{
				animationComponent->SetAnimation(PlayerAnimationState::Drop);
			}
		}
		//浮上中ならジャンプアニメーションへ
		else
		{
			animationComponent->SetAnimation(PlayerAnimationState::Jump);
		}
	}
	//回避中なら回避アニメーションを再生
	if (avoidancing)
	{
		animationComponent->SetAnimation(PlayerAnimationState::Avoidance);
	}
	else
	{
		SetScale(60.0f);

	}
	//ジャンプにより浮上中か
	if (velocity.y <= 0)
	{
		isFloating = false;
	}
	else
	{
		isFloating = true;
	}
	CandleHealingIntervalDown();
	Friction(MoveFriction);
	AcoidanceIntervalDown();
	SetPosition(position + (velocity));
	Invincible();
	SkeletonThinGround();
	DrawHitPointUI();
}

/*
@fn 入力を管理
*/
void PlayerCharacter::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	if (!avoidancing)
	{
		inputDirection = 0;
	}
	inputUnderDirection = false;

	//コントローラーが接続された場合操作をコントローラーに変更
	if (InputSystem::GetConnectedController())
	{
		inputDirection = _keyState.Controller.GetLAxisVec().x;
		inputUnderDirection = _keyState.Controller.GetLAxisVec().y >= 0.7f ? 1.0f : 0.0f;
	}
	else
	{
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
		{
			inputDirection = 1;
		}
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
		{
			inputDirection = -1;
		}
		inputUnderDirection = _keyState.Keyboard.GetKeyValue(SDL_SCANCODE_DOWN);
	}
	if (inputDirection == 0 && avoidancing)
	{
		inputDirection = direction;
	}
	//if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_DOWN))
	//{
	//	inputUnderDirection = true;
	//}

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X);
	rangeAttackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_S) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y);
	avoidanceBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_D) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B);
	jumpBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A);
	attack->SetInput(_keyState.Keyboard.GetKeyState(SDL_SCANCODE_Q) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER),
		_keyState.Keyboard.GetKeyState(SDL_SCANCODE_E) || _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER));

	//前Fと入力法が違い、スティックの入力が0でない場合プレイヤーの向きを更新
	if (direction != inputDirection && inputDirection != 0)
	{
		direction = inputDirection > 0 ? 1.0f : -1.0f;
		bool reverce = direction == 1.0f ? false : true;
		animationComponent->SetReverce(reverce);
	}

	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_3))
	{
		Game::debug = 0;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_4))
	{
		Game::debug = 1;
	}
}

/*
@fn めり込み判定
*/
void PlayerCharacter::FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag)
{
	//浮上中でかつ薄い床にすでに接触している場合はめりこみ補正を行わない
	if (_pairTag == Tag::ThinGroundFloor)
	{
		if ((isFloating && isThinGroundCollision) || doSkeletonThinGround)
		{
			return;
		}
	}
	Vector3 ment = Vector3(0, 0, 0);
	calcCollisionFixVec(myAABB, pairAABB, ment);
	SetPosition(GetPosition() + (ment));
}

/*
@fn オブジェクト全体が停止している状態で、死亡していた時処理を行う
*/
void PlayerCharacter::PausingUpdateGameObject()
{
	if (pauzingEvent == PauzingEvent::DeadPlayerEvent)
	{
		//velocity.y = -1;
		//SetPosition(position + velocity);
		Friction(DownFriction);
		animationComponent->SetAnimation(PlayerAnimationState::Down);
		if (velocity.x >= -1 && velocity.x <= 1)
		{
			pauzingEvent = PauzingEvent::GameOverEvent;
		}
	}
}

/*
@fn ゲームオーバーになったか
*/
bool PlayerCharacter::GetGameOver()
{
	if (hitPoint <= 0)
	{
		return true;
	}
	return false;
}

void PlayerCharacter::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::ThinGroundFloor)
	{
		isThinGroundCollision = true;
		return;
	}
	if (colliderPair->GetObjectTag() == Tag::CandleStickTag)
	{
		if (candleHealingInterval < 0)
		{
			if (hitPoint < HitPointMax)
			{
				hitPoint++;
				new HeartParticleEffect(position, Vector3(0, 2.5, 0), false);
			}
			candleHealingInterval = 100;
		}
		return;
	}
}

void PlayerCharacter::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyWeaponTag)
	{
		if (!invincible && !avoidancing)
		{
			//衝突した敵の攻撃が、防御済みでないか
			//if (!guardComponent->SearchObjectId(colliderPair->GetId()))
			//{
				//プレイヤーの攻撃の方向を計算しnockBackForceに計算
			double distance = Math::Sqrt((colliderPair->GetPosition().x - position.x) * (colliderPair->GetPosition().x - position.x) + (colliderPair->GetPosition().y - position.y) * (colliderPair->GetPosition().y - position.y));
			Vector3 force = Vector3::Normalize(Vector3((position.x - colliderPair->GetPosition().x), 0, (position.z - colliderPair->GetPosition().z)));
			velocity.x = force.x * 10;
			animationComponent->SetAnimation(PlayerAnimationState::Outi);
			HitAttack();
			//}
		}
	}
}

/*
@fn プレイヤーが行うアクション
*/
void PlayerCharacter::Actions(float _deltaTime, const bool& _noGround)
{
	bool actioned = false;
	if ((attackBottonInput || rangeAttackBottonInput) && !avoidancing)
	{
		bool rangeAttack = false;
		if (attackBottonInput)
		{
			canNotActionTime = attack->Attack(direction, 1, rangeAttack);
		}
		else if (rangeAttackBottonInput)
		{
			canNotActionTime = attack->Attack(direction, 2, rangeAttack);
		}
		if (animationComponent != nullptr)
		{
			if (!rangeAttack)
			{
				animationComponent->SetAnimation(PlayerAnimationState::Attack);
				velocity.x += -0.6f * direction;
			}
			else
			{
				animationComponent->SetAnimation(PlayerAnimationState::Range);
			}
		}
		actioned = true;
	}
	else
	{
		//Guard();
		Avoidance();
		if (inputDirection != 0 || avoidancing)
		{
			Move(_deltaTime);
			actioned = true;
		}

		//着地しているか
		if (!_noGround)
		{
			doubleJump = false;
			doubleJumpInterval = 0;
			if (jumpBottonInput)
			{
				Jump();
				actioned = true;
			}
			//animationComponent->SetAnimation();
		}
		//下方向への入力があるか
		if (inputUnderDirection > 0)
		{
			//薄い床のすり抜け可能な時間のディレイをセット
			inputUnderCount = InputUnderCountMax;
		}
	}
	if (!actioned)
	{
		if (velocity.y == 0)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Idle);
		}
	}
}


void PlayerCharacter::Avoidance()
{
	if (avoidanceBottonInput)
	{
		if (avoidanceInterval <= 0)
		{
			avoidancing = true;
			animationComponent->SetAnimation(PlayerAnimationState::Avoidance);
			avoidanceInterval = AvoidanceInterval;
			invincibleCount = AvoidanceInvincible;
		}
	}
}

void PlayerCharacter::AcoidanceIntervalDown()
{
	if (avoidanceInterval <= 0)
	{

	}
	else
	{
		avoidanceInterval--;
	}
}

void PlayerCharacter::Move(float _deltaTime)
{
	if (inputDirection != 0)
	{
		if (animationComponent != nullptr && velocity.y == 0)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Move);
		}
		float speed = MoveSpeed;
		if (avoidancing)
		{
			speed *= 1.15f;
		}
		velocity.x = (speed * _deltaTime) * inputDirection;
	}
	else
	{
		//if (animationComponent != nullptr)
		//{
		//	animationComponent->SetAnimation(PlayerAnimationState::Idle);
		//}
	}
}

void PlayerCharacter::SkeletonThinGround()
{
	//下方向への入力があった後ほかに変化がなくカウントが過ぎた場合すべてリセットする
	if (inputUnderCount <= 0)
	{
		inputUnderCount = 0;
		noInputForUnderDirection = false;
		doSkeletonThinGround = false;
	}
	else
	{
		inputUnderCount--;
		//下方向への入力があったあと1未満の下方向への入力(ニュートラル)があった場合
		if (inputUnderDirection < 1)
		{
			noInputForUnderDirection = true;
		}
	}
	//下方向への入力がありその直後ニュートラルにする等の操作が入ったらすり抜けを実行
	if (noInputForUnderDirection && inputUnderDirection > 0)
	{
		inputUnderCount = 0;
		noInputForUnderDirection = false;
		doSkeletonThinGround = true;
	}
}

void PlayerCharacter::Jump()
{
	//上下への移動力をリセット
	//if (!isThinGroundCollision)
	{
	}
	if (velocity.y <= 0)
	{
		velocity.y = 0;
		velocity.y += JumpPower;
		doubleJumpInterval = 0;
	}
	else
	{

	}

}

void PlayerCharacter::Gravity(float _deltaTime)
{
	velocity.y += -GravityPower /* _deltaTime*/;

	if (velocity.y <= -25)
	{
		velocity.y = -25;
	}
}

void PlayerCharacter::Friction(float _fricton)
{
	//velocityが一定以下でないなら左右移動へ摩擦を付与
	if (velocity.x >= 0.1f && velocity.x <= -0.1f)
	{
		velocity.x = 0;
	}
	else
	{
		velocity.x /= _fricton;
	}
}

void PlayerCharacter::HitAttack()
{
	invincibleCount = InvincibleCount;
	invincible = true;
	new HeartParticleEffect(position, Vector3(15, 2.5, 0), true);
	new HeartParticleEffect(position, Vector3(-15, 2.5, 0), true);
	new HeartParticleEffect(position, Vector3(5, 2.5, 0), true);
	if (hitPoint <= 0)
	{
		isLive = false;
		pauzingEvent = PauzingEvent::DeadPlayerEvent;
	}
	else
	{
		hitPoint--;
	}
}

void PlayerCharacter::Invincible()
{
	if (invincibleCount <= 0)
	{
		invincible = false;
		avoidancing = false;
	}
	else
	{
		invincibleCount--;
	}
}

void PlayerCharacter::DrawHitPointUI()
{
	unsigned int unsignedHitPoint = hitPoint;
	if (hitPointUI.size() < unsignedHitPoint)
	{
		for (; hitPointUI.size() < unsignedHitPoint;)
		{
			hitPointUI.emplace_back(new UserInterfaceBase(HitPointUIPos + Vector3(HitPointUIWidth * hitPointUI.size(), 0, 0),
				"Assets/Image/UI/HpGreen.png", Vector3(HitPointUISize, HitPointUISize, HitPointUISize), 900));
		}
	}
	else if (hitPointUI.size() > unsignedHitPoint)
	{
		if (!hitPointUI.empty())
		{
			for (; hitPointUI.size() > unsignedHitPoint;)
			{
				delete hitPointUI.back();
				hitPointUI.pop_back();
				new HaveLifeCountUI(HitPointUIPos + Vector3(HitPointUIWidth * hitPointUI.size(), 0, 0),
					"Assets/Image/UI/HpGreen.png", 30, Vector3(HitPointUISize, HitPointUISize, HitPointUISize), 900);
			}
		}
	}
}

void PlayerCharacter::CandleHealingIntervalDown()
{
	if (candleHealingInterval >= 0)
	{
		candleHealingInterval--;
	}
}
