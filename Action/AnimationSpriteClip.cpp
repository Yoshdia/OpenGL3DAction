#include "AnimationSpriteClip.h"
#include "Texture.h"

AnimationSpriteClip::AnimationSpriteClip()
{
	nowAnimationFrame = 0;
	nowAnimationTime = 0;
	animation = new AnimationKeyFrame[10];
	for (int num = 0; num < 10; num++)
	{
		animation[num].sprite = nullptr;
		animation[num].waitTimeForNextTexture = 0;
	}
}

AnimationSpriteClip::~AnimationSpriteClip()
{
	if (animation != nullptr)
	{
		delete[] animation;
	}
}

void AnimationSpriteClip::Animation()
{
	if (nowAnimationTime < animation[nowAnimationFrame].waitTimeForNextTexture)
	{
		nowAnimationTime++;
	}
	else
	{
		nowAnimationFrame++;
		if (animation[nowAnimationFrame].sprite == nullptr)
		{
			animationEnd = true;
			nowAnimationFrame = 0;
		}

		nowAnimationTime = 0;
	}
}

void AnimationSpriteClip::ResetAnimation()
{
	nowAnimationFrame = 0;
	nowAnimationTime = 0;
}
