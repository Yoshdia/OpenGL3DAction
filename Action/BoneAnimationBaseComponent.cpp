#include "BoneAnimationBaseComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Renderer.h"

/*
@fn ���b�V���f�[�^�N���X���m��
*/
BoneAnimationBaseComponent::BoneAnimationBaseComponent(GameObject * _owner, int updateOrder) :
	Component(_owner,updateOrder),
	startFlash(false),
	flashColor(0),
	plusFlashColor(false)
{
	skeltalMeshComponent = new SkeletalMeshComponent(_owner);
}

BoneAnimationBaseComponent::~BoneAnimationBaseComponent()
{
}

/*
 @fn �h���N���X�Ō��肷��֐��Ɣ����֐�Flash()���X�V����
*/
void BoneAnimationBaseComponent::Update(float _deltaTime)
{
	Flash();
	UpdateAnimationComponent(_deltaTime);
}

/*
 @fn �������s���t���O�������Ă���Ƃ��A���b�V���J���[�𑝌��������b�V���f�[�^�ɐF����n��
*/
void BoneAnimationBaseComponent::Flash()
{
	//�������s����
	if (startFlash)
	{
		//�F�𔒂֑�������
		if (plusFlashColor)
		{
			//���ɂȂ�܂ŐF�𑝂₵���ɂȂ�����t���O��|��
			if (flashColor > 1.0f)
			{
				flashColor = 1.0f;
				plusFlashColor = false;
			}
			else
			{
				flashColor += 0.2f;
			}
		}
		else
		{
			//�F��0�ɂȂ�܂Ō���������
			if (flashColor < 0)
			{
				flashColor = 0;
				startFlash = false;
			}
			else
			{
				flashColor -= 0.2f;
			}
		}
		//���b�V���f�[�^�ɐF�𑗂�
		skeltalMeshComponent->SetColor(Vector3(flashColor, flashColor, flashColor));
	}
}
