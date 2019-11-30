#include "AnimationPlayerComponent.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "MovePlayerAnimationClip.h"
#include "IdlePlayerAnimationClip.h"
#include "AttackPlayerAnimationClip.h"
#include "RangeAttackPlayerAnimationClip.h"
#include "Texture.h"

AnimationPlayerComponent::AnimationPlayerComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	particleComponent = new ParticleComponent(_owner,Vector3(0,5.0f,0),1);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));

	nowAnimation = nullptr;
	idle = new IdlePlayerAnimationClip();
	move = new MovePlayerAnimationClip();
	attack = new AttackPlayerAnimationClip();
	rangeAttack = new RangeAttackPlayerAnimationClip();

	nowAnimation = idle;
	beforeAnimation = PlayerAnimationState::Idle;
	nextAnimation = PlayerAnimationState::Idle;

}

AnimationPlayerComponent::~AnimationPlayerComponent()
{
	nowAnimation = nullptr;
	delete idle;
	delete move;
	delete attack;
	delete rangeAttack;
}

void AnimationPlayerComponent::Update(float _deltaTime)
{
	if (nowAnimation != nullptr)
	{
		particleComponent->SetTextureID(nowAnimation->GetSprite()->GetTextureID());
	}
	nowAnimation->Animation();

	if (beforeAnimation != nextAnimation)
	{
		switch (nextAnimation)
		{
		case (PlayerAnimationState::Idle): nowAnimation = idle; break;
		case (PlayerAnimationState::Move): nowAnimation = move; break;
		case (PlayerAnimationState::Attack): nowAnimation = attack; break;
		case (PlayerAnimationState::Range): nowAnimation = rangeAttack; break;
		}
		nowAnimation->ResetAnimation();
	}

	beforeAnimation = nextAnimation;
}
