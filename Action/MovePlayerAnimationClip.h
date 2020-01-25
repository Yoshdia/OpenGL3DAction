#pragma once
#include "AnimationSpriteClip.h"
#include <string>

/*
 @file MovePlayerAnimationClip.h
 @fn 移動しているプレイヤーのアニメーション
*/
class MovePlayerAnimationClip final :
	public AnimationSpriteClip 
{
public:
	MovePlayerAnimationClip();
	~MovePlayerAnimationClip();
};

