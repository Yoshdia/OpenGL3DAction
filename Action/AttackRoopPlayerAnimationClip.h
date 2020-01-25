#pragma once
#include "AnimationSpriteClip.h"

/*
 @file AttackRoopPlayerAnimationClip.h
 @fn 攻撃を行い続けているプレイヤーのアニメーション。AttackPlayerAnimationClipの後にループして再生する
*/
class AttackRoopPlayerAnimationClip :
	public AnimationSpriteClip
{
public:
	AttackRoopPlayerAnimationClip();
	~AttackRoopPlayerAnimationClip();
};

