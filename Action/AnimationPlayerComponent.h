#pragma once
#include "Component.h"

enum PlayerAnimationState
{
	Idle,
	Move,
	Attack,
	AttackRoop,
	Range,
	RangeRoop,
	Guard,
	Down,
	Outi,
	Jump,
	Drop,
};

class AnimationSpriteClip;

class AnimationPlayerComponent :
	public Component
{
public:
	AnimationPlayerComponent(GameObject* _owner, int _updateOrder);
	~AnimationPlayerComponent();
	void Update(float _deltaTime)override;
	void SetAnimation(const PlayerAnimationState& _state);
private:
	class ParticleComponent* particleComponent;
	AnimationSpriteClip* nowAnimation;
	AnimationSpriteClip* idle;
	AnimationSpriteClip* move;
	AnimationSpriteClip* attack;
	AnimationSpriteClip* attackRoop;
	AnimationSpriteClip* rangeAttack;
	AnimationSpriteClip* rangeAttackRoop;
	AnimationSpriteClip* outi;
	AnimationSpriteClip* guard;
	AnimationSpriteClip* down;
	AnimationSpriteClip* jump;
	AnimationSpriteClip* dropping;


	PlayerAnimationState nextAnimation;
	PlayerAnimationState beforeAnimation;
};

