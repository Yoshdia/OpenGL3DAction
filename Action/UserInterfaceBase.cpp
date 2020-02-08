#include "UserInterfaceBase.h"
#include "SpriteComponent.h"
#include "Renderer.h"

/*
@param _pos �X�N���[�����W
@param _spriteName �摜�ւ̃A�h���X
@param _size �T�C�Y
@param _drawOrder �`�揇
*/
UserInterfaceBase::UserInterfaceBase(const Vector3 & _pos, const std::string & _spriteName,const Vector3& _size ,const int& _drawOrder)
{
	SetPosition(_pos);
	SetScale(_size);
	spriteComponent = new SpriteComponent(this, _drawOrder);
	spriteComponent->SetTexture(RENDERER->GetTexture(_spriteName));
}

UserInterfaceBase::~UserInterfaceBase()
{
}
