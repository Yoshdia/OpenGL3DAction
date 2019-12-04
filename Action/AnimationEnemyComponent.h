#pragma once
#include "BoneAnimationBaseComponent.h"
class AnimationEnemyComponent :
	public BoneAnimationBaseComponent
{
public:
	AnimationEnemyComponent(GameObject * _owner, int updateOrder=100);
	~AnimationEnemyComponent();

	void UpdateAnimationComponent(float _deltaTime)override;

	void SetMove(bool _move) { move = _move; };
private:
	const class Animation* moveAnim;
	const class Animation* idleAnim;

	enum EnemyAnimationName
	{
		Idle,
		Move,
	};
	EnemyAnimationName animationName;
	bool move;
	float animDuration;
};

