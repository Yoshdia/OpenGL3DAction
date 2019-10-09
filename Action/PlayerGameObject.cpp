#include "PlayerGameObject.h"
#include "SpriteComponent.h"
#include "Renderer.h"

PlayerGameObject::PlayerGameObject():
	GameObject()
{
	spriteComponent = new SpriteComponent(this, 100);
	spriteComponent->SetTexture(Renderer::GetInstance()->GetTexture("Assets/Image/once.png"));
	printf("%5f,%5f,%5f", position.x,position.y,position.z);
	SetPosition(Vector3(0, 0, 10));
}

PlayerGameObject::~PlayerGameObject()
{
}

void PlayerGameObject::UpdateGameObject(float _deltaTime)
{
}

void PlayerGameObject::GameObjectInput(const InputState & _keyState)
{
}
