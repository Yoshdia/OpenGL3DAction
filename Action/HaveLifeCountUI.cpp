#include "HaveLifeCountUI.h"
#include "SpriteComponent.h"
#include "Renderer.h"

HaveLifeCountUI::HaveLifeCountUI(const Vector3 & _pos, const std::string & spriteName, int _lifeCount, const Vector3 & _size, const int & _drawOrder):
	UserInterfaceBase(_pos, spriteName, _size, _drawOrder),
	lifeCount(_lifeCount)
{
	spriteComponent->SetTexture(RENDERER->GetTexture("Assets/Image/UI/HpRed.png"));
}

HaveLifeCountUI::~HaveLifeCountUI()
{
}

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
