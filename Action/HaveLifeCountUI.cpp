#include "HaveLifeCountUI.h"
#include "SpriteComponent.h"
#include "Renderer.h"

/*
@param _pos �X�N���[�����W
@param _spriteName �摜�ւ̃A�h���X
@param _lifeCount ��������
@param _size �T�C�Y
@param _drawOrder �`�揇
*/
HaveLifeCountUI::HaveLifeCountUI(const Vector3 & _pos, const std::string & _spriteName, int _lifeCount, const Vector3 & _size, const int & _drawOrder):
	UserInterfaceBase(_pos, _spriteName, _size, _drawOrder),
	lifeCount(_lifeCount)
{
	spriteComponent->SetTexture(RENDERER->GetTexture("Assets/Image/UI/HpRed.png"));
}

HaveLifeCountUI::~HaveLifeCountUI()
{
}

/*
@fn �������Ԃ��J�E���g����
*/
void HaveLifeCountUI::UpdateGameObject(float _deltaTime)
{
	if (lifeCount <= 0)
	{
		SetState(State::Dead);
	}
	else
	{
		lifeCount--;
	}
}
