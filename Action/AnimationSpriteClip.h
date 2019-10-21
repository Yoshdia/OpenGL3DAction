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
protected:
	AnimationKeyFrame* animation;
	//現在描画中のSprite
	Texture* nowSprite;

	int nowAnimationTime;
	int nowAnimationFrame;
	bool animationEnd;
};

