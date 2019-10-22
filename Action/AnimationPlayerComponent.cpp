#include "AnimationPlayerComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "MovePlayerAnimationClip.h"

AnimationPlayerComponent::AnimationPlayerComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	spriteComponent = new SpriteComponent(_owner, 100);

	nowAnimation = nullptr;
	idle =new MovePlayerAnimationClip();

	nowAnimation = idle;
}

AnimationPlayerComponent::~AnimationPlayerComponent()
{
	nowAnimation = nullptr;
	delete idle;
}

void AnimationPlayerComponent::Update(float _deltaTime)
{
	if (nowAnimation != nullptr)
	{
		spriteComponent->SetTexture(nowAnimation->GetSprite());
	}
	nowAnimation->Animation();
}
