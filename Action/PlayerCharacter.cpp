#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include "InputSystem.h"

PlayerCharacter::PlayerCharacter()
{
	spriteComponent = new SpriteComponent(this, 100);
	spriteComponent->SetTexture(Renderer::GetInstance()->GetTexture("Assets/Image/once.png"));
	printf("%5f,%5f,%5f", position.x, position.y, position.z);
	SetPosition(Vector3(0, 0, 0));
	MeshComponent* mesh = new MeshComponent(this);
	mesh->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
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
		dir.z++;
	}
	if (_keyState.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		dir.z--;
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

