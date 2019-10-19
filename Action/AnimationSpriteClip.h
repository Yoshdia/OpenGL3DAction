#pragma once
class Texture;

/*
 @file AnimationSpriteClip.h
 @brief Spriteのアニメーションクリップ基底クラス
*/
class AnimationSpriteClip abstract
{
public:
	AnimationSpriteClip();
	virtual ~AnimationSpriteClip();

	/*
   @fn Clip内で次のSpriteへ移行する関数
   @detail AnimationComponent内でのnowSpriteCountが一定数まで増えたので、nowTextureを次のSpriteへ変更し、nowSpriteCountの最大数を変更させこのクラスのnowTextureCountを変更する
   @return 次描画させるSpriteのアドレス
  */
	virtual const Texture* ChangeNextTexture(int& spriteCountMax);
protected:
	//現在描画中のSprite
	Texture* nowSprite;
	int nowSpriteCount;

};

