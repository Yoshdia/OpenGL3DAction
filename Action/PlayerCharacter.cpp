#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "InputSystem.h"
#include "AnimationPlayerComponent.h"
#include "AttackPlayerComponent.h"
#include "ColliderComponent.h"
#include "InputMovePlayerComponent.h"
//#include "PhysicsWorld.h"
#include "FootSole.h"
#include "MeshComponent.h"


const float PlayerCharacter::jumpPower = 60;

PlayerCharacter::PlayerCharacter() :
	GameObject(),
	movement(Vector3(5, 5, 5)),
	inputDirection(Vector3(0, 0, 0)),
	attackBottonInput(false),
	canNotActionTime(0),
	isJump(false),
	velo(Vector3(0, 0, 0))
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);

	tag = Tag::PlayerTag;
	SetPosition(Vector3(100, 100, 0));
	SetScale(25);

	//animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	std::function<void(ColliderComponent*)>  Enter = std::bind(&PlayerCharacter::OnTriggerEnter, this, std::placeholders::_1);
	std::function<void(ColliderComponent*)>  Stay = std::bind(&PlayerCharacter::OnTriggerStay, this, std::placeholders::_1);
	ColliderComponent* colliderComponent = new ColliderComponent(this, 100, Vector3(50, 50, 50), myObjectId, Enter, Stay, tag, Vector3(0, 0, 0));
	inputMovePlayerComponent = new InputMovePlayerComponent(this, 100);

	footSole = new FootSole(this);

	MeshComponent* meshComponent = new MeshComponent(this);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/untitled.gpmesh"));
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	RENDERER->SetViewMatrixLerpObject(Vector3(0, 0, -500), position);
	if (canNotActionTime < 0)
	{
		if (inputDirection != Vector3::Zero)
		{
			if (animationComponent != nullptr)
			{
				animationComponent->SetAnimation(PlayerAnimationState::Move);
			}
		}
		else
		{
			if (animationComponent != nullptr)
			{
				animationComponent->SetAnimation(PlayerAnimationState::Idle);
			}
		}

		if (attackBottonInput == true)
		{
			if (attack != nullptr)
			{
				canNotActionTime = attack->Attack();
			}
			if (animationComponent != nullptr)
			{
				animationComponent->SetAnimation(PlayerAnimationState::Attack);
			}
		}
	}
	else
	{
		canNotActionTime--;
	}
	SetPosition(position + (inputDirection * movement));
}

void PlayerCharacter::GameObjectInput(const InputState& _keyState)
{
	if (_keyState.Keyboard.GetKeyValue(SDL_SCANCODE_0) == 1)
		printf("\nplayerPosition = {%f,%f,%f}", position.x, position.y, position.z);

	//inputDirection = inputMovePlayerComponent->InputMoveMent(_keyState);
	inputDirection = Vector3::Zero;
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		inputDirection.x++;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		inputDirection.x--;
	}

	attackBottonInput = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_A);

	isJump = footSole->GetGroundFlag();
	if (!isJump)
	{
		velo = Vector3::Zero;
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) || _keyState.Keyboard.GetKeyState(SDL_SCANCODE_L))
		{
			velo.y += 35;
		}
	}
	else
	{
		velo.y += -2;
	}
	SetPosition(position + velo);
}



void PlayerCharacter::OnTriggerStay(ColliderComponent* colliderPair)
{
	if (colliderPair->GetObjectTag() == Tag::EnemyTag)
	{
		printf("IYAAAAAAAA\n");
	}
}
