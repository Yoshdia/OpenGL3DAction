#pragma once
#include "Component.h"

enum PlayerAnimationState
{
	Idle,
	Move,
	Attack,
	Range,
};

class AnimationSpriteClip;

class AnimationPlayerComponent :
	public Component
{
public:
	AnimationPlayerComponent(GameObject* _owner, int _updateOrder);
	~AnimationPlayerComponent();
	void Update(float _deltaTime)override;
	void SetAnimation(const PlayerAnimationState& _state) {nextAnimation = _state;};
private:
	class ParticleComponent* particleComponent;
	AnimationSpriteClip* nowAnimation;
	AnimationSpriteClip* idle;
	AnimationSpriteClip* move;
	AnimationSpriteClip* attack;
	AnimationSpriteClip* rangeAttack;

	PlayerAnimationState nextAnimation;
	PlayerAnimationState beforeAnimation;
};

