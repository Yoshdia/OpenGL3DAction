#pragma once
#include "AnimationSpriteClip.h"
#include <string>

/*
 @file MovePlayerAnimationClip.h
 @brief Player�̈ړ��A�j���[�V�����N���b�v
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

