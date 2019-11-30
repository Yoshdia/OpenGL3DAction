#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "InputSystem.h"
#include "AttackPlayerComponent.h"
#include "ColliderComponent.h"
//#include "PhysicsWorld.h"
#include "MeshComponent.h"
#include "SkeltonObjectChecker.h"
#include "GuardPlayerComponent.h"
#include "ParticleComponent.h"
#include "Texture.h"

const float PlayerCharacter::MoveSpeed = 600;
const float PlayerCharacter::MoveSpeedLimit = 10.0f;
const float PlayerCharacter::GravityPower = 80;
const float PlayerCharacter::GravityPowerLimit = 1.2f;
const float PlayerCharacter::JumpPower = 25.0f;
const float PlayerCharacter::MoveFriction = 1.2f;

const int PlayerCharacter::InvincibleCount = 120;

PlayerCharacter::PlayerCharacter() :
	GameObject(),
	inputDirection(0),
	canNotActionTime(0),
	velocity(Vector3(0, 0, 0)),
	attackBottonInput(false),
	jumpBottonInput(false),
	rangeAttackBottonInput(false),
	guardBottonInput(false),
	direction(1),
	invincible(false),
	invincibleCount(0)

{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	SetPosition(Vector3(100, 200, 0));
	float scaleF = 25.0f;
	SetScale(scaleF);

	//animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	guardComponent = new GuardPlayerComponent(this, 100);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, GetTriggerEnterFunc(), GetTriggerStayFunc(), tag, Vector3(0, 0, 0));

	footChecker = new SkeltonObjectChecker(this, Vector3(0, -scaleF, 0), Vector3(20, 1, 20), Tag::GroundTag);

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	// パーティクルのセット　これはあとでパーティクルエミッタクラス作りたい。

	Vector3 randV((rand() % 100) / 10.0f, (rand() % 100) / 10.0f, (rand() % 100) / 10.0f);
	Vector3 Velocity = randV * 0.1f;
	Velocity.x += -0.5f;
	Velocity.y += -0.5f;
	Velocity.z += 2.5f;

	// 後にパーティクル発生用クラス作成する
	// 3フレームに1回　パーティクル発生
	static int frame = 0;
	frame++;
	if (frame % 5 == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			Vector3 pos;
			pos = Vector3(-0, 0, 0);
			pos = pos + randV;

			ParticleComponent* p = new ParticleComponent(this, pos,
				Velocity,
				1, 1.0f,
				randV.x * 0.5f);

			p->SetTextureID((RENDERER->GetTexture("Assets/fire.png"))->GetTextureID());
			p->SetColor(Vector3(1.0f, 0.5f, 0.2f));
			p->SetBlendMode(ParticleComponent::PARTICLE_BLEND_ENUM_ADD);
			p->SetIsFollowing(false);
		}
	}
	//カメラの追跡先をセット
	//RENDERER->SetViewMatrixLerpObject(Vector3(0, 0, -500), position);
	//着地状態
	bool noGround = footChecker->GetNoTouchingFlag();
	//入力によるアクションができるか
	if (canNotActionTime < 0)
	{
		Actions(_deltaTime,noGround);
	}
	else
	{
		canNotActionTime--;
	}
	//空中なら重力を付与
	if (noGround)
	{
		Gravity(_deltaTime);
	}
	Friction();
	SetPosition(position + (velocity));
	Invincible();
}

void PlayerCharacter::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	inputDirection = 0;
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		direction = 1;
		inputDirection++;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		direction = -1;
		inputDirection--;
	}

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A);
	rangeAttackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_S);
	guardBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_D);
	jumpBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE);

	//if (_keyState.Controller.GetIsConnected())
	//{
	//	attackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B);
	//	rangeAttackBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A);
	//	jumpBottonInput = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y);
	//}
	//if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_1))
		//RENDERER->SetViewMatrixLerpObject(Vector3(0, 0, -200), position);
}

void PlayerCharacter::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyTag)
	{
	}
}

void PlayerCharacter::OnTriggerEnter(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyWeaponTag)
	{
		if (!invincible)
		{
			//衝突した敵の攻撃が、防御済みでないか
			if (!guardComponent->SearchObjectId(colliderPair->GetId()))
			{
				HitAttack();
				printf("Outi!!!!\n");
			}
		}
	}
}

void PlayerCharacter::Actions(float _deltaTime,const bool& _noGround)
{
	Move(_deltaTime);
	//着地しているか
	if (!_noGround)
	{
		Jump();
	}
	if (attackBottonInput)
	{
		Attack(PlayerAnimationState::Attack);
	}
	else if (rangeAttackBottonInput)
	{
		Attack(PlayerAnimationState::Range);
	}
	else if (guardBottonInput)
	{
		Guard();
	}
}

void PlayerCharacter::Attack(PlayerAnimationState _animState)
{
	switch (_animState)
	{
	case(PlayerAnimationState::Attack):
		if (attack != nullptr)
		{
			canNotActionTime = attack->Attack(direction);
		}
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Attack);
		}
		break;
	case(PlayerAnimationState::Range):
		if (attack != nullptr)
		{
			canNotActionTime = attack->RangeAttack(direction);
		}
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Range);
		}
		break;
	}
}

void PlayerCharacter::Guard()
{
	canNotActionTime = guardComponent->Guard();
}

void PlayerCharacter::Move(float _deltaTime)
{
	if (inputDirection != 0)
	{
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Move);
		}
		float moveSpeedDelta = (MoveSpeed * _deltaTime) * inputDirection;
		moveSpeedDelta=	ControlDeltaLimit(moveSpeedDelta, MoveSpeedLimit);
		moveSpeedDelta=ControlDeltaLimit(moveSpeedDelta, -MoveSpeedLimit);
		velocity.x = moveSpeedDelta;
	}
	else
	{
		if (animationComponent != nullptr)
		{
			animationComponent->SetAnimation(PlayerAnimationState::Idle);
		}
	}
}

void PlayerCharacter::Jump()
{
	//上下への移動力をリセット
	velocity.y = 0;
	if (jumpBottonInput)
	{
		velocity.y += JumpPower;
	}
}

void PlayerCharacter::Gravity(float _deltaTime)
{
	float gravityDelta = ControlDeltaLimit(GravityPower * _deltaTime, GravityPowerLimit);
	velocity.y += -gravityDelta;
}

void PlayerCharacter::Friction()
{
	//velocityが一定以下でないなら左右移動へ摩擦を付与
	if (velocity.x >= 0.1f && velocity.x <= -0.1f)
	{
		velocity.x = 0;
	}
	else
	{
		velocity.x /= MoveFriction;
	}
}

void PlayerCharacter::HitAttack()
{
	invincibleCount = InvincibleCount;
	invincible = true;
}

void PlayerCharacter::Invincible()
{
	if (!invincible)
	{
		return;
	}
	if (invincibleCount <= 0)
	{
		invincible = false;
	}
	else
	{
		invincibleCount--;
	}
}
