#pragma once
#include "AnimationSpriteClip.h"
#include <string>

/*
 @file MovePlayerAnimationClip.h
 @brief Playerの移動アニメーションクリップ
*/
class MovePlayerAnimationClip final :
	public AnimationSpriteClip 
{
public:
	MovePlayerAnimationClip();
	~MovePlayerAnimationClip();

	//const Texture* ChangeNextTexture(int& spriteCountMax);
private:

	////std::string fileNameone;
	//std::string fileNametwo;
};

