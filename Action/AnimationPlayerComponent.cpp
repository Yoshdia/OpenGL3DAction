#include "AnimationPlayerComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"

AnimationPlayerComponent::AnimationPlayerComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	spriteComponent = new SpriteComponent(_owner, 100);
	spriteComponent->SetTexture(Renderer::GetInstance()->GetTexture("Assets/Image/once.png"));
}

AnimationPlayerComponent::~AnimationPlayerComponent()
{
}

void AnimationPlayerComponent::Update(float _deltaTime)
{
}
