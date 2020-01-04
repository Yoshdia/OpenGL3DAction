#include "AnimationPlayerComponent.h"
#include "ParticleComponent.h"
#include "Renderer.h"
#include "MovePlayerAnimationClip.h"
#include "IdlePlayerAnimationClip.h"
#include "AttackPlayerAnimationClip.h"
#include "RangeAttackPlayerAnimationClip.h"
#include "Texture.h"
#include "DownPlayerAnimationClip.h"
#include "GuardPlayerAnimationClip.h"
#include "JumpPlayerAnimationClip.h"
#include "NockBackPlayerAnimationClip.h"
#include "DroppingDownPlayerAnimation.h"
#include "AnimationSpriteClip.h"
#include "AttackRoopPlayerAnimationClip.h"
#include "RangeAttackRoopAnimationClip.h"

AnimationPlayerComponent::AnimationPlayerComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
	particleComponent = new ParticleComponent(_owner, Vector3(0, 5.0f, 0), 1);
	particleComponent->SetColor(Vector3(1.0f, 1.0f, 1.0f));

	nowAnimation = nullptr;
	idle = new IdlePlayerAnimationClip();
	move = new MovePlayerAnimationClip();
	attack = new AttackPlayerAnimationClip();
	attackRoop = new AttackRoopPlayerAnimationClip();
	rangeAttack = new RangeAttackPlayerAnimationClip();
	rangeAttackRoop = new RangeAttackRoopAnimationClip();
	outi = new NockBackPlayerAnimationClip();
	guard = new GuardPlayerAnimationClip();
	down = new DownPlayerAnimationClip();
	jump = new JumpPlayerAnimationClip();
	dropping = new DroppingDownPlayerAnimation();

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
	delete attackRoop;
	delete rangeAttack;
	delete rangeAttackRoop;
	delete outi;
	delete guard;
	delete down;
	delete jump;
	delete dropping;
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
		case (PlayerAnimationState::Down): nowAnimation = down; break;
		case (PlayerAnimationState::Guard): nowAnimation = guard; break;
		case (PlayerAnimationState::Jump): nowAnimation = jump; break;
		case (PlayerAnimationState::Outi): nowAnimation = outi; break;
		case (PlayerAnimationState::Drop): nowAnimation = dropping; break;
		}
		nowAnimation->ResetAnimation();
	}
	if (nextAnimation == PlayerAnimationState::Attack)
	{
		if (nowAnimation->AnimationEnd())
		{
			printf("loooooooop\n");
			nowAnimation = attackRoop;
			nextAnimation = PlayerAnimationState::AttackRoop;
		}
	}
	else if(nextAnimation == PlayerAnimationState::Range)
	{
		if (nowAnimation->AnimationEnd())
		{
			printf("loooooooop\n");
			nowAnimation = rangeAttackRoop;
			nextAnimation = PlayerAnimationState::RangeRoop;
		}
	}

	beforeAnimation = nextAnimation;
}

void AnimationPlayerComponent::SetAnimation(const PlayerAnimationState & _state)
{
	if ((beforeAnimation == PlayerAnimationState::AttackRoop&&_state==PlayerAnimationState::Attack)|| 
		(beforeAnimation == PlayerAnimationState::RangeRoop&&_state == PlayerAnimationState::Range))
	{
		return;
	}
	nextAnimation = _state;
}
