#pragma once
class Texture;

/*
 @struct �A�j���[�V�����̒���1�t���[���ɕK�v�ȏ��
 @fn �A���ōĐ�����A�j���[�V������1�t���[��
*/
struct AnimationKeyFrame
{
	//�\������e�N�X�`��
	Texture* sprite;
	//���̃e�N�X�`���܂ł̑ҋ@���ԁA���͌��e�N�X�`���̕\������
	int waitTimeForNextTexture;
};

/*
 @file AnimationSpriteClip.h
 @fn Sprite�̃A�j���[�V�����N���b�v���N���X
*/
class AnimationSpriteClip abstract
{
public:
	/*
	 @fn �������Ă���S�̃A�j���[�V�����̏�����
	*/
	AnimationSpriteClip();
	/*
	 @fn �������Ă���S�̃A�j���[�V�����̉��
	*/
	virtual ~AnimationSpriteClip();

	/*
	 @fn �A�j���[�V�������s��
	*/
	void Animation();

	/*
	 @fn �A�j���[�V���������Z�b�g
	*/
	void ResetAnimation();
protected:
	//�A�j���[�V����
	AnimationKeyFrame* animation;
	//���݂̃e�N�X�`���̕\������
	int nowAnimationTime;
	//���݂̃A�j���[�V��������
	int nowAnimationCount;
	//�A�j���[�V�������I��������
	bool animationEnd;
	//�A�j���[�V���������[�v���邩
	bool loop;
public: //�Q�b�^�[�Z�b�^�[
	/*
	 @fn ���ݍĐ����̃e�N�X�`����Ԃ�
	*/
	Texture* GetSprite() { return animation[nowAnimationCount].sprite; }
	/*
	 @fn �A�j���[�V�������I��������
	*/
	bool GetAnimationEnd() { return animationEnd; }
	/*
	 @fn ���[�v���s�����ǂ����̃t���O
	*/
	bool GetLoopFlag() { return loop; }
};

