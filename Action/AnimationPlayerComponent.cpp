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
	outi = new NockBackPlayerAnimationClip();
	guard = new GuardPlayerAnimationClip();
	down = new DownPlayerAnimationClip();
	jump = new JumpPlayerAnimationClip();

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
	delete outi;
	delete guard;
	delete down;
	delete jump;
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
		case (PlayerAnimationState::Guard): nowAnimation = guard;break;
		case (PlayerAnimationState::Jump): nowAnimation = jump;break;
		case (PlayerAnimationState::Outi): nowAnimation = outi; break;
		}
		nowAnimation->ResetAnimation();
	}

	beforeAnimation = nextAnimation;
}
