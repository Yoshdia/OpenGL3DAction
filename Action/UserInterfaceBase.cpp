#include "UserInterfaceBase.h"
#include "SpriteComponent.h"
#include "Renderer.h"

UserInterfaceBase::UserInterfaceBase(const Vector3 & _pos, const std::string & spriteName)
{
	SetPosition(_pos);
	SpriteComponent* spriteComponent = new SpriteComponent(this);
	spriteComponent->SetTexture(RENDERER->GetTexture(spriteName));
}

UserInterfaceBase::~UserInterfaceBase()
{
}
