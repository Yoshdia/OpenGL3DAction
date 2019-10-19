#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "InputSystem.h"
#include "AnimationPlayerComponent.h"

PlayerCharacter::PlayerCharacter()
{
	printf("%5f,%5f,%5f", position.x, position.y, position.z);
	SetPosition(Vector3(0, 0, 0));
	animationComponent = new AnimationPlayerComponent(this, 100);
	//camera=new CameraComponent(this);
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
	Vector3 dir = Vector3( 0,0,0 );
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

	SetPosition(position + dir);
}

