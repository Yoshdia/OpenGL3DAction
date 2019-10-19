#include "AnimationSpriteClip.h"
#include "Texture.h"

AnimationSpriteClip::AnimationSpriteClip()
{
	nowSprite = nullptr;
}

AnimationSpriteClip::~AnimationSpriteClip()
{
	if (nowSprite != nullptr)
	{
		delete nowSprite;
		nowSprite = nullptr;
	}
}

const Texture * AnimationSpriteClip::ChangeNextTexture(int& spriteCountMax)
{
	return nullptr;
}