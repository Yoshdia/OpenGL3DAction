#include "HaveLifeCountUI.h"
#include "SpriteComponent.h"
#include "Renderer.h"

/*
@param _pos スクリーン座標
@param _spriteName 画像へのアドレス
@param _lifeCount 生存時間
@param _size サイズ
@param _drawOrder 描画順
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
@fn 生存時間をカウントする
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
