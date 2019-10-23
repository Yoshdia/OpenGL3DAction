#pragma once
#include "Component.h"

enum PlayerAnimationState
{
	Idle,
	Move,
	Attack,
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
	class SpriteComponent* spriteComponent;
	AnimationSpriteClip* nowAnimation;
	AnimationSpriteClip* idle;
	AnimationSpriteClip* move;
	AnimationSpriteClip* attack;

	PlayerAnimationState nextAnimation;
	PlayerAnimationState beforeAnimation;
};

