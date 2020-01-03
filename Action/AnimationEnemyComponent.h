#pragma once
#include "BoneAnimationBaseComponent.h"

enum EnemyType
{
	MeleeType,
	RangeType,
	TankType,
	MageType,
};

class AnimationEnemyComponent :
	public BoneAnimationBaseComponent
{
public:
	AnimationEnemyComponent(GameObject * _owner, EnemyType _type, int updateOrder = 100);
	~AnimationEnemyComponent();

	void UpdateAnimationComponent(float _deltaTime)override;


	/*
	@fn アニメーションの残り時間を返す
	*/
	float GetAnimDuration() { return animDuration; }
	void SetMove(bool _move) { move = _move; };
	void SetAttack(bool _attack) { attack = _attack; }
	void SetSpawn(bool _spawn) { spawn = _spawn; }
	void SetStan(bool _stan) { stan = _stan; }
	void SetAction(bool _action) { action = _action; }
private:
	const class Animation* moveAnim;
	const class Animation* idleAnim;
	const class Animation* attackAnim;

	const class Animation* spawnAnim;
	const class Animation* stanAnim;
	const class Animation* actionAnim;

	enum EnemyAnimationName
	{
		Idle,
		Move,
		Attack,
		Spawn,
		Stan,
		Action,
	};
	EnemyAnimationName animationName;

	bool move;
	bool attack;
	bool spawn;
	bool stan;
	bool action;
	float animDuration;
};

