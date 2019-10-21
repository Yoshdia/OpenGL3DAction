#pragma once
class Texture;

struct AnimationKeyFrame
{
	Texture* sprite;
	int waitTimeForNextTexture;
};

/*
 @file AnimationSpriteClip.h
 @brief Sprite�̃A�j���[�V�����N���b�v���N���X
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
	//���ݕ`�撆��Sprite
	Texture* nowSprite;

	int nowAnimationTime;
	int nowAnimationFrame;
	bool animationEnd;
};

