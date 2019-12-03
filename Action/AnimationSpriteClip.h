#pragma once
class Texture;

struct AnimationKeyFrame
{
	Texture* sprite;
	int waitTimeForNextTexture;
};

/*
 @file AnimationSpriteClip.h
 @brief Spriteのアニメーションクリップ基底クラス
*/
class AnimationSpriteClip abstract
{
public:
	AnimationSpriteClip();
	virtual ~AnimationSpriteClip();

	void Animation();
	Texture* GetSprite() { return animation[nowAnimationFrame].sprite; };
	bool AnimationEnd() { return animationEnd; };
	void ResetAnimation();

	bool GetLoopFlag() { return loop; }
protected:
	AnimationKeyFrame* animation;

	int nowAnimationTime;
	int nowAnimationFrame;
	bool animationEnd;

	bool loop;
};

