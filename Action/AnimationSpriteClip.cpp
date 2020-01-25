#include "AnimationSpriteClip.h"
#include "Texture.h"

/*
 @fn 所持している全体アニメーションの初期化
*/
AnimationSpriteClip::AnimationSpriteClip() :
	nowAnimationCount(0),
	nowAnimationTime(0),
	loop(false),
	animationEnd(false)
{
	animation = new AnimationKeyFrame[10];
	for (int num = 0; num < 10; num++)
	{
		animation[num].sprite = nullptr;
		animation[num].waitTimeForNextTexture = 0;
	}
}

/*
 @fn 所持している全体アニメーションの解放
*/
AnimationSpriteClip::~AnimationSpriteClip()
{
	if (animation != nullptr)
	{
		delete[] animation;
	}
}

/*
 @fn アニメーションを行う
*/
void AnimationSpriteClip::Animation()
{
	//アニメーションが終了していてかつループするかそうでないか
	if (animationEnd&&!loop)
	{
		return;
	}
	//現在のアニメーションカウントが再生中のテクスチャ表示時間を超えていないか
	if (nowAnimationTime < animation[nowAnimationCount].waitTimeForNextTexture)
	{
		nowAnimationTime++;
	}
	//超えた場合
	else
	{
		//次のアニメーションへ
		nowAnimationCount++;
		//次のアニメーションが存在しない場合nullptrが返ってくるので終了
		if (animation[nowAnimationCount].sprite == nullptr)
		{
			//アニメーション終了
			animationEnd = true;
			//ループするか、する場合再生枚数を初期化
			if (loop)
			{
				nowAnimationCount = 0;
			}
			else
			{
				nowAnimationCount--;
			}
		}
		nowAnimationTime = 0;
	}
}

/*
 @fn アニメーションをリセット
*/
void AnimationSpriteClip::ResetAnimation()
{
	nowAnimationCount = 0;
	nowAnimationTime = 0;
	animationEnd = false;
}
