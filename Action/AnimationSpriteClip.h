#pragma once
class Texture;

/*
 @struct アニメーションの中の1フレームに必要な情報
 @fn 連続で再生するアニメーションの1フレーム
*/
struct AnimationKeyFrame
{
	//表示するテクスチャ
	Texture* sprite;
	//次のテクスチャまでの待機時間、又は現テクスチャの表示時間
	int waitTimeForNextTexture;
};

/*
 @file AnimationSpriteClip.h
 @fn Spriteのアニメーションクリップ基底クラス
*/
class AnimationSpriteClip abstract
{
public:
	/*
	 @fn 所持している全体アニメーションの初期化
	*/
	AnimationSpriteClip();
	/*
	 @fn 所持している全体アニメーションの解放
	*/
	virtual ~AnimationSpriteClip();

	/*
	 @fn アニメーションを行う
	*/
	void Animation();

	/*
	 @fn アニメーションをリセット
	*/
	void ResetAnimation();
protected:
	//アニメーション
	AnimationKeyFrame* animation;
	//現在のテクスチャの表示時間
	int nowAnimationTime;
	//現在のアニメーション枚数
	int nowAnimationCount;
	//アニメーションが終了したか
	bool animationEnd;
	//アニメーションをループするか
	bool loop;
public: //ゲッターセッター
	/*
	 @fn 現在再生中のテクスチャを返す
	*/
	Texture* GetSprite() { return animation[nowAnimationCount].sprite; }
	/*
	 @fn アニメーションが終了したか
	*/
	bool GetAnimationEnd() { return animationEnd; }
	/*
	 @fn ループを行うかどうかのフラグ
	*/
	bool GetLoopFlag() { return loop; }
};

