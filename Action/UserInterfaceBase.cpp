#include "UserInterfaceBase.h"
#include "SpriteComponent.h"
#include "Renderer.h"

UserInterfaceBase::UserInterfaceBase(const Vector3 & _pos, const std::string & spriteName,const Vector3& _size ,const int& _drawOrder)
{
	SetPosition(_pos);
	SetScale(_size);
	spriteComponent = new SpriteComponent(this, _drawOrder);
	spriteComponent->SetTexture(RENDERER->GetTexture(spriteName));
}

UserInterfaceBase::~UserInterfaceBase()
{
}
