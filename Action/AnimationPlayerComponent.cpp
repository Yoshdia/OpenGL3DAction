#include "AnimationPlayerComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "MovePlayerAnimationClip.h"
#include "IdlePlayerAnimationClip.h"
#include "AttackPlayerAnimationClip.h"

AnimationPlayerComponent::AnimationPlayerComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	spriteComponent = new SpriteComponent(_owner, 100);

	nowAnimation = nullptr;
	idle =new IdlePlayerAnimationClip();
	move =new MovePlayerAnimationClip();
	attack = new AttackPlayerAnimationClip();

	nowAnimation = idle;
	beforeAnimation = PlayerAnimationState::Idle;
	nextAnimation=PlayerAnimationState::Idle;
}

AnimationPlayerComponent::~AnimationPlayerComponent()
{
	nowAnimation = nullptr;
	delete idle;
	delete move;
	delete attack;
}

void AnimationPlayerComponent::Update(float _deltaTime)
{
	if (nowAnimation != nullptr)
	{
		spriteComponent->SetTexture(nowAnimation->GetSprite());
	}
	nowAnimation->Animation();

	if (beforeAnimation != nextAnimation)
	{
		switch (nextAnimation)
		{
		case (PlayerAnimationState::Idle): nowAnimation = idle; break;
		case (PlayerAnimationState::Move): nowAnimation = move; break;
		case (PlayerAnimationState::Attack): nowAnimation = attack; break;
		}
		nowAnimation->ResetAnimation();
	}

	beforeAnimation = nextAnimation;
}
