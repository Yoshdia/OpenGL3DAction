#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "InputSystem.h"
#include "AnimationPlayerComponent.h"
#include "AttackPlayerComponent.h"

PlayerCharacter::PlayerCharacter()
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);
	SetPosition(Vector3(0, 0, 0));
	animationComponent = new AnimationPlayerComponent(this, 100);
	attack = new AttackPlayerComponent(this, 100);
	//camera=new CameraComponent(this);
	canNotActionTime = 0;
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	//camera->Update(_deltaTime);
}

void PlayerCharacter::GameObjectInput(const InputState & _keyState)
{
	if (canNotActionTime < 0)
	{
		{
			Vector3 dir = Vector3(0, 0, 0);
			bool moving = false;
			if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
			{
				dir.x++;
			}
			if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
			{
				dir.x--;
			}
			if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_UP))
			{
				dir.y++;
			}
			if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_DOWN))
			{
				dir.y--;
			}
			if (dir != Vector3::Zero)
			{
				moving = true;
			}
			if (moving)
			{
				animationComponent->SetMove();
			}
			else
			{
				animationComponent->SetIdle();
			}
			SetPosition(position + dir);
		}
		if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE))
		{
			canNotActionTime = attack->Attack();
		}
	}
	else
	{
		canNotActionTime--;
	}
}

