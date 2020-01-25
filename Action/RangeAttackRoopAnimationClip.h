#pragma once
#include "AnimationSpriteClip.h"

/*
 @file RangeAttackRoopAnimationClip.h
 @fn 遠距離攻撃を行い続けているプレイヤーのアニメーションAttackPlayerAnimationClipの後にループして再生する
*/
class RangeAttackRoopAnimationClip :
	public AnimationSpriteClip
{
public:
	RangeAttackRoopAnimationClip();
	~RangeAttackRoopAnimationClip();
};

