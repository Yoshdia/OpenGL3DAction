#pragma once
class Texture;

/*
 @file AnimationSpriteClip.h
 @brief Sprite�̃A�j���[�V�����N���b�v���N���X
*/
class AnimationSpriteClip abstract
{
public:
	AnimationSpriteClip();
	virtual ~AnimationSpriteClip();

	/*
   @fn Clip���Ŏ���Sprite�ֈڍs����֐�
   @detail AnimationComponent���ł�nowSpriteCount����萔�܂ő������̂ŁAnowTexture������Sprite�֕ύX���AnowSpriteCount�̍ő吔��ύX�������̃N���X��nowTextureCount��ύX����
   @return ���`�悳����Sprite�̃A�h���X
  */
	virtual const Texture* ChangeNextTexture(int& spriteCountMax);
protected:
	//���ݕ`�撆��Sprite
	Texture* nowSprite;
	int nowSpriteCount;

};

