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
	void SetAttack(bool _attack) { attack = _attack; }
private:
	const class Animation* moveAnim;
	const class Animation* idleAnim;
	const class Animation* attackAnim;

	enum EnemyAnimationName
	{
		Idle,
		Move,
		Attack,
	};
	EnemyAnimationName animationName;
	bool move;
	bool attack;
	float animDuration;
};

