#include "TakeItemUi.h"

/*
@param _pos �J�n���W
@param _targetSlot �ړI�n
@param _spriteName �摜�A�h���X
@param _size �摜�T�C�Y
*/
TakeItemUi::TakeItemUi(const Vector3& _pos, const Vector3& targetSlot, const std::string& _spriteName, const Vector3& _size) :
	UserInterfaceBase(_pos, _spriteName, _size, 100),
	life(240)
{
	target = targetSlot;
}

TakeItemUi::~TakeItemUi()
{
}

/*
@fn ���W����ڕW�܂ňړ����A�������Ԃ��J�E���g�_�E������
*/
void TakeItemUi::UpdateGameObject(float _deltaTime)
{
	SetPosition(Vector3::Lerp(position, target, 0.05f));
	if (life < 0)
	{
		SetState(State::Dead);
	}
	else
	{
		life--;
	}
}
