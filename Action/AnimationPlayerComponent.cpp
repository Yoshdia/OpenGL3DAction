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
#include "AvoidancingPlayerAnimation.h"

/*
@fn アニメーションクラスの確保
*/
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
	avoidancing = new AvoidancingPlayerAnimation();


	nowAnimation = idle;
	beforeAnimation = PlayerAnimationState::Idle;
	nextAnimation = PlayerAnimationState::Idle;

}

/*
@fn アニメーションクラスの解放
*/
AnimationPlayerComponent::~AnimationPlayerComponent()
{
	nowAnimation = nullptr;
	delete idle;
	delete move;
	delete attack;
	delete attackRoop;
	delete avoidancing;
	delete rangeAttack;
	delete rangeAttackRoop;
	delete outi;
	delete guard;
	delete down;
	delete jump;
	delete dropping;
}

/*
@fn nowAnimationを更新しながらnextAnimationを参照し変更を行う
*/
void AnimationPlayerComponent::Update(float _deltaTime)
{
	//アニメーションが終了していないなら再生する
	if (nowAnimation != nullptr)
	{
		particleComponent->SetTextureID(nowAnimation->GetSprite()->GetTextureID());
	}
	nowAnimation->Animation();

	//次に再生するアニメーションを設定
	if (beforeAnimation != nextAnimation)
	{
		switch (nextAnimation)
		{
		case (PlayerAnimationState::Idle): nowAnimation = idle; break;
		case (PlayerAnimationState::Move): nowAnimation = move; break;
		case (PlayerAnimationState::Attack): nowAnimation = attack; break;
		case (PlayerAnimationState::Range): nowAnimation = rangeAttack; break;
		case (PlayerAnimationState::Down): //ダウン時は座標に対する画像の位置を変更する
			nowAnimation = down; particleComponent->SetOffSet(Vector3(0, 0, 0)); break;
		case (PlayerAnimationState::Guard): nowAnimation = guard; break;
		case (PlayerAnimationState::Jump): nowAnimation = jump; break;
		case (PlayerAnimationState::Outi): nowAnimation = outi; break;
		case (PlayerAnimationState::Drop): nowAnimation = dropping; break;
		case (PlayerAnimationState::Avoidance): nowAnimation = avoidancing; break;
		}
		nowAnimation->ResetAnimation();
	}

	//攻撃アニメーションが終了したとき自動で攻撃ループのアニメーションへ移動する
	if (nextAnimation == PlayerAnimationState::Attack)
	{
		if (nowAnimation->GetAnimationEnd())
		{
			nowAnimation = attackRoop;
			nextAnimation = PlayerAnimationState::AttackRoop;
		}
	}
	//遠距離攻撃アニメーションが終了したとき自動で遠距離攻撃ループのアニメーションへ移動する
	else if(nextAnimation == PlayerAnimationState::Range)
	{
		if (nowAnimation->GetAnimationEnd())
		{
			nowAnimation = rangeAttackRoop;
			nextAnimation = PlayerAnimationState::RangeRoop;
		}
	}

	beforeAnimation = nextAnimation;
}

/*
@fn 次に再生するアニメーションを設定
*/
void AnimationPlayerComponent::SetAnimation(const PlayerAnimationState & _state)
{
	if ((beforeAnimation == PlayerAnimationState::AttackRoop&&_state==PlayerAnimationState::Attack)|| 
		(beforeAnimation == PlayerAnimationState::RangeRoop&&_state == PlayerAnimationState::Range))
	{
		return;
	}
	nextAnimation = _state;
}

/*
@fn パーティクルを反転するか
*/
void AnimationPlayerComponent::SetReverce(bool _flag)
{
	particleComponent->SetReverce(_flag);
}
