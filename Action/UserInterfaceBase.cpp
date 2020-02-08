#include "UserInterfaceBase.h"
#include "SpriteComponent.h"
#include "Renderer.h"

/*
@param _pos スクリーン座標
@param _spriteName 画像へのアドレス
@param _size サイズ
@param _drawOrder 描画順
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
