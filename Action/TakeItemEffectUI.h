#pragma once
#include "UserInterfaceBase.h"

/*
@file TakeItemEffectUI.h
@brief �A�C�e�����擾�����Ƃ��Ɏg�p�����A�T�C�Y���g�債�Ȃ�����T�C�Y�܂ł����ƍX�V���~�߂�
*/
class TakeItemEffectUI :
	public UserInterfaceBase
{
public:
	/*
	@param _pos �X�N���[�����W
	*/
	TakeItemEffectUI(const Vector3& _pos);
	~TakeItemEffectUI();
	/*
	@fn �T�C�Y���g�債�Ȃ�����T�C�Y�܂ł����ƍX�V���~�߂�
	*/
	void UpdateGameObject(float _deltaTime)override;
private:
	float spriteScale;
};

