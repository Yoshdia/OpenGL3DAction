#include "PlayerCharacter.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CameraComponent.h"
#include "MeshComponent.h"

PlayerCharacter::PlayerCharacter()
{
	spriteComponent = new SpriteComponent(this, 100);
	spriteComponent->SetTexture(Renderer::GetInstance()->GetTexture("Assets/Image/once.png"));
	printf("%5f,%5f,%5f", position.x, position.y, position.z);
	SetPosition(Vector3(00, 00, 0));

	camera=new CameraComponent(this);
}


PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::UpdateGameObject(float _deltaTime)
{
	camera->Update(_deltaTime);
}
