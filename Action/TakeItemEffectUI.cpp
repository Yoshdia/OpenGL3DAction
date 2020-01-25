#include "TakeItemEffectUI.h"
#include "SpriteComponent.h"


TakeItemEffectUI::TakeItemEffectUI(const Vector3& _pos):
	UserInterfaceBase(_pos,"Assets/Image/UI/SquareWhiteBox.png",Vector3(1,1,1),50),
	spriteScale(6.0f)
{

}


TakeItemEffectUI::~TakeItemEffectUI()
{
}

void TakeItemEffectUI::UpdateGameObject(float _deltaTime)
{
	spriteScale+=0.5f;
	if (spriteScale >= 10)
	{
		spriteScale = 10;
		
		SetState(State::Dead);
	}
	SetScale(spriteScale);
}
