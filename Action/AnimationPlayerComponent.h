#pragma once
#include "Component.h"

enum PlayerAnimationState
{
	Idle,
	Move,
};

class AnimationSpriteClip;

class AnimationPlayerComponent :
	public Component
{
public:
	AnimationPlayerComponent(GameObject* _owner, int _updateOrder);
	~AnimationPlayerComponent();
	void Update(float _deltaTime)override;
private:
	class SpriteComponent* spriteComponent;
	AnimationSpriteClip* nowAnimation;
	AnimationSpriteClip* idle;
};

